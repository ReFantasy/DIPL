#include <iostream>      
#include "opencv2/opencv.hpp"
#include "utility/utility.hpp"
#include "algorithm/algorithm.hpp"

using namespace std;
using namespace cv;

void MouseHandle(int event, int x, int y, int flags, void* param);

Mat Cross(const Mat a, const Mat b);
Mat Connected(const Mat A, cv::Point pt);

int GetSpecificPixelNumber(const Mat src, int gray_level);

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
	cout << "使用鼠标点击 src 窗口中的白色连通分量..." << endl;
	namedWindow("src");
	namedWindow("res");
	
	Mat src = imread("../data/DIP3E_Original_Images_CH09/Fig0918(a)(Chickenfilet with bones).tif", 0);
	cv::threshold(src, src, 205, 255, CV_THRESH_BINARY);
	imshow("src", src);

	Mat res(src.rows, src.cols, CV_8UC1, Scalar(0));

	cv::Point pt;
	setMouseCallback("src", MouseHandle, &src);
	while (1)
	{
		imshow("res", res);
		waitKey(0);          //直到有按键按下
	}

	imshow("src", src);
	waitKey();
	return 0;
}

int GetSpecificPixelNumber(const Mat src, int gray_level)
{
	int n = 0;
	for (auto itor = src.begin<uchar>(); itor != src.end<uchar>(); itor++)
	{
		if ((*itor) == gray_level)n++;
	}
	return n;
}

void MouseHandle(int event, int x, int y, int flags, void* param)
{
	Point pt;
	switch (event)
	{
		//左键按下消息
		case EVENT_LBUTTONDOWN:
		{
			pt = Point(x, y);
			const Mat src = *(Mat *)(param);
			auto res = Connected(src, pt);
			int connect_count = GetSpecificPixelNumber(res, 255);
			cout << "连通的像素数量：" << connect_count << endl;
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

Mat Connected(const Mat A, cv::Point pt)
{
	Mat B = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

	// opencv 膨胀白色区域，所以需要设置背景为黑色
	Mat X0(A.rows, A.cols, CV_8UC1, Scalar(0));
	X0.at<uchar>(pt) = 255;

	Mat tmp;
	dilate(X0, tmp, B);

	Mat X1 = Cross(tmp, A);
	

	Mat X_K = X1;
	Mat X_K_1 = X0;

	while (!IsSame(X_K,X_K_1))
	{
		X_K_1 = X_K;
		dilate(X_K_1, tmp, B);
		X_K = Cross(tmp, A);	
	}
	
	return X_K;
}

