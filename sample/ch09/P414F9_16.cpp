#include <iostream>      
#include "opencv2/opencv.hpp"
#include "utility/utility.hpp"
#include "algorithm/algorithm.hpp"

using namespace std;
using namespace cv;

void MouseHandle(int event, int x, int y, int flags, void* param);

Mat Cross(const Mat a, const Mat b);
Mat Connected(Mat A, cv::Point pt);

bool IsSame(const Mat A, const Mat B)
{
	Mat dif = A - B;
	for (auto it = dif.begin<uchar>(); it != dif.end<uchar>(); it++)
	{
		if (*it != 0)
			return false;
	}

	return true;
}

int main(int argc, char*argv[])
{
	cout << "使用鼠标点击 res 窗口中的孔洞..." << endl;
	namedWindow("src");
	namedWindow("res");
	
	Mat src = imread("../data/DIP3E_Original_Images_CH09/Fig0916(a)(region-filling-reflections).tif", 0);
	imshow("src", src);

	Mat res = src.clone();

	cv::Point pt;
	setMouseCallback("res", MouseHandle, &res);
	while (1)
	{
		imshow("res", res);
		waitKey(0);          //直到有按键按下
	}

	imshow("src", src);

	
	waitKey();
	return 0;
}

void MouseHandle(int event, int x, int y, int flags, void* param)
{
	Point pt;
	static Mat src = (*(Mat *)(param)).clone();
	switch (event)
	{
		//左键按下消息
		case EVENT_LBUTTONDOWN:
		{
			pt = Point(x, y);
			Mat res = *(Mat *)(param);
			res = Connected(res, pt);
			bitwise_or(src, res, res);
			src = res.clone();
			imshow("res", res);
		}
	    break;

	}
}

Mat Cross(const Mat a, const Mat b)
{
	Mat res(a.rows, a.cols, CV_8UC1, Scalar(255));
	int rows = a.rows;
	int cols = a.cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (a.data[i*cols + j] == b.data[i*cols + j])
			{
				res.data[i*cols + j] = a.data[i*cols + j];
			}
			else
			{
				res.data[i*cols + j] = 0;
			}
		}
	}

	return res;
}

Mat Connected(Mat A, cv::Point pt)
{
	Mat A_C; 
	cv::bitwise_not(A, A_C);  

	Mat B = getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));

	// opencv 膨胀白色区域，所以需要设置背景为黑色
	Mat X0(A.rows, A.cols, CV_8UC1, Scalar(0));
	X0.at<uchar>(pt) = 255;

	Mat tmp;
	dilate(X0, tmp, B);

	Mat X1 = Cross(tmp, A_C);
	

	Mat X_K = X1;
	Mat X_K_1 = X0;

	while (!IsSame(X_K,X_K_1))
	{
		X_K_1 = X_K;
		dilate(X_K_1, tmp, B);
		X_K = Cross(tmp, A_C);	
	}

	return X_K;
}

