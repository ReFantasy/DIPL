#include <iostream>      
#include <vector>
#include "opencv2/opencv.hpp"

#include "algorithm/algorithm.hpp"
#include "utility/utility.hpp"



using namespace std;


int main(int argc, char *argv[])
{
	Mat a = imread("../data/DIP3E_Original_Images_CH05/Fig0520(a)(NASA_Mariner6_Mars).tif", 0);
	resize(a, a, { 512,512 });
	int rows = a.rows;
	int cols = a.cols;

	auto a_vec = IPL::Mat2Vector2D(a);
	auto a_fourier = IPL::Fourier::FFT(a_vec);

	auto b = IPL::ShowFourier(a_fourier);


	imshow("a", a);
	imshow("b", b);
	

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
	cv::normalize(temp[0], show, 1, 0, NORM_MINMAX);
	cv::imshow(name, show);
	return notch_pass;
}




