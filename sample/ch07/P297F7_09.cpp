#include <iostream>      
#include "opencv2/opencv.hpp"
#include "algorithm/algorithm.hpp"
#include "utility/utility.hpp"


using namespace std;

constexpr int K = 8;

double G0(int n);
double G1(int n)
{
	return std::pow(-1, n)*G0(K - 1 - n);
}

double H0(int n)
{
	return G0(K - 1 - n);
}

double H1(int n)
{
	return G1(K - 1 - n);
}

std::vector<std::vector<double>> ConvHoriz(const std::vector<std::vector<double>> &src,
	double(*F)(int) , int kern_size)
{
	int rows = src.size();
	int cols = src[0].size();

	auto res = src;
	int hf = kern_size / 2;

	for (int i = 0; i < rows; i++)
	{
		for (int j = hf; j < cols - hf; j++)
		{
			double tmp = 0;
			for (int index = j - hf, n=0; index < j + hf; index++)
			{
				//cout << index + hf << endl;
				//auto f = F(index + hf);
				tmp += src[i][index] * F(n++);
			}
			res[i][j] = tmp;
		}
	}

	return res;
}

std::vector<std::vector<double>> ConvVert(const std::vector<std::vector<double>> &src,
	double(*F)(int), int kern_size)
{
	int rows = src.size();
	int cols = src[0].size();

	auto res = src;
	int hf = kern_size / 2;
	for (int j = 0; j < cols; j++)
	{
		for (int i = hf; i < rows-hf; i++)
		{
			double tmp = 0;
			for (int index = i - hf, n= 0; index < i + hf; index++)
			{
				tmp += src[index][j] * F(n++);
			}
			res[i][j] = tmp;
		}
	}

	return res;
}


int main(int argc, char *argv[])
{
	Mat src = imread("../data/DIP3E_Original_Images_CH07/vase.tif", 0);

	auto src_vec = IPL::Mat2Vector2D(src);

	auto h0m = ConvHoriz(src_vec, H0, K);
	h0m = IPL::PryDownByRow(h0m);
	auto h0n = ConvVert(h0m, H0, K);
	h0n = IPL::PryDownByCol(h0n);
	auto a = IPL::NormalizeVec2DToMat(h0n);

	auto h1n = ConvVert(h0m, H1, K);
	h1n = IPL::PryDownByCol(h1n);
	auto b = IPL::NormalizeVec2DToMat(h1n);
	cv::equalizeHist(b, b);

	auto h1m = ConvHoriz(src_vec, H1, K);
	h1m = IPL::PryDownByRow(h1m);
	h0n = ConvVert(h1m, H0, K);
	h0n = IPL::PryDownByCol(h0n);
	auto c = IPL::NormalizeVec2DToMat(h0n);
	cv::equalizeHist(c, c);

	h1n = ConvVert(h1m, H1, K);
	h1n = IPL::PryDownByCol(h1n);
	auto d = IPL::NormalizeVec2DToMat(h1n);
	cv::equalizeHist(d, d);

	imshow("a", a);
	imshow("b", b);
	imshow("c", c);
	imshow("d", d);
	waitKey();
	return 0;


}

double G0(int n)
{
	static std::vector<double> table = {
		0.23037781,
	    0.71484657,
	    0.63088076,
       -0.02798376,
       -0.18703481,
	    0.03084138,
	    0.03288301,
       -0.01059740
	};
	return table[n];
}




