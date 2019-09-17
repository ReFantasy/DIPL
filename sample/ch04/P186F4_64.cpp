#include <iostream>      
#include <vector>
#include "opencv2/opencv.hpp"

#include "algorithm/algorithm.hpp"
#include "utility/utility.hpp"



using namespace std;


int main(int argc, char *argv[])
{
	Mat a = imread("../data/DIP3E_Original_Images_CH04/Fig0464(a)(car_75DPI_Moire).tif", 0);
	int rows = a.rows;
	int cols = a.cols;

	// 傅里叶变换并显示傅里叶谱
	auto src_vec = IPL::Mat2CentreVector2D(a);
	auto src_fourier = IPL::Fourier::DFT(src_vec);
	Mat b(rows, cols, CV_64FC1);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			b.at<double>(i, j) = log(1 + abs(src_fourier[i][j]));
		}
	}
	normalize(b, b, 0, 1, NORM_MINMAX);


	// 生成陷波滤波器
	std::vector<double> D0s;
	std::vector<std::pair<int, int>> uks;
	int D = 8;
	int n = 4;
	
	D0s.push_back(D);
	uks.push_back({ rows * 40 / 250.0,cols / 3.0 });
	D0s.push_back(D);
	uks.push_back({ rows * 40 / 250.0,cols / 3.0 * 2 });

	D0s.push_back(D);
	uks.push_back({ rows * 80 / 250.0,cols / 3.0 });
	D0s.push_back(D);
	uks.push_back({ rows * 80 / 250.0,cols / 3.0 * 2 });


	D0s.push_back(D);
	uks.push_back({ rows * (250-40) / 250.0,cols / 3.0 });
	D0s.push_back(D);
	uks.push_back({ rows * (250-40) / 250.0,cols / 3.0 * 2 });

	D0s.push_back(D);
	uks.push_back({ rows * (250-80) / 250.0,cols / 3.0 });
	D0s.push_back(D);
	uks.push_back({ rows * (250 - 80) / 250.0,cols / 3.0 * 2 });

	auto nbpf = IPL::NBSF(rows, cols, D0s, uks, n);


	// 对傅里叶谱的图像应用陷波滤波器
	Mat c(rows, cols, CV_64FC1);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			c.at<double>(i, j) = nbpf[i][j] * b.at<double>(i, j);
		}
	}
	normalize(c, c, 0, 1, NORM_MINMAX);


	// 对原图像的傅里叶变换应用陷波滤波器
	auto _idft = src_fourier;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			_idft[i][j] = nbpf[i][j] * src_fourier[i][j];
		}
	}
	auto idft = IPL::Fourier::IDFT(_idft);
	Mat d(rows, cols, CV_64FC1);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			d.at<double>(i, j) = abs(idft[i][j] * pow(-1,i+j));
		}
	}
	normalize(d, d, 0, 1, NORM_MINMAX);

	imshow("a", a);
	imshow("b", b);
	imshow("c", c);
	imshow("d", d);


	
	

	waitKey();
	return 0;
}

//陷波滤波器
cv::Mat notch_kernel(cv::Mat &scr, std::vector<cv::Point> &notch_pot, float D0)
{
	cv::Mat notch_pass(scr.size(), CV_32FC2);
	int row_num = scr.rows;
	int col_num = scr.cols;
	int n = 4;

	for (int i = 0; i < row_num; i++)
	{
		float *p = notch_pass.ptr<float>(i);

		for (int j = 0; j < col_num; j++)
		{
			float h_nr = 1.0;
			for (unsigned int k = 0; k < notch_pot.size(); k++)
			{
				int u_k = notch_pot.at(k).y;
				int v_k = notch_pot.at(k).x;
				float dk = sqrt(pow((i - u_k), 2) + pow((j - v_k), 2));
				float d_k = sqrt(pow((i + u_k), 2) + pow((j + v_k), 2));
				float dst_dk = 1.0 / (1.0 + pow(D0 / dk, 2 * n));
				float dst_d_k = 1.0 / (1.0 + pow(D0 / d_k, 2 * n));
				h_nr = dst_dk * dst_d_k * h_nr;
				// std::cout <<  "notch_pot: " << notch_pot.at(k) << std::endl;
			}


			p[2 * j] = h_nr;
			p[2 * j + 1] = h_nr;
		}
	}

	cv::Mat temp[] = { cv::Mat::zeros(scr.size(), CV_32FC1),
					   cv::Mat::zeros(scr.size(), CV_32FC1) };
	cv::split(notch_pass, temp);

	std::string name = "notch滤波器d0=" + std::to_string(D0);
	cv::Mat show;
	cv::normalize(temp[0], show, 1, 0, CV_MINMAX);

	

	cv::imshow(name, show);
	return notch_pass;
}




