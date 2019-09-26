#include <iostream>      
#include "opencv2/opencv.hpp"
#include "algorithm/algorithm.hpp"
#include "utility/utility.hpp"


using namespace std;
using Vec2D = std::vector<std::vector<double>>;

extern int K;

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

template<typename T>
std::vector<std::vector<T>> ConvHoriz(const std::vector<std::vector<T>> &src,
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
			T tmp{};
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

template<typename T>
std::vector<std::vector<T>> ConvVert(const std::vector<std::vector<T>> &src,
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
			T tmp{};
			for (int index = i - hf, n= 0; index < i + hf; index++)
			{
				tmp += src[index][j] * F(n++);
			}
			res[i][j] = tmp;
		}
	}

	return res;
}

void SubbandCode(const Vec2D &src, Vec2D &dst_a, Vec2D &dst_dV, Vec2D &dst_dH, Vec2D &dst_dD);

template<typename T>
std::vector<std::vector<T>> Vec2DAdd(const std::vector<std::vector<T>> &a, const std::vector<std::vector<T>> &b)
{
	int rows = a.size();
	int cols = a[0].size();
	auto res = a;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			res[i][j] = a[i][j] + b[i][j];
		}
	}
	return res;
}
int main(int argc, char *argv[])
{

	Mat src = imread("../data/DIP3E_Original_Images_CH07/vase.tif", 0);
	resize(src, src, { 512,512 });
	auto src_vec = IPL::Mat2Vector2D(src);

	auto src_vec_fourier = IPL::Fourier::FFT(src_vec);

	auto h0n = ConvHoriz(src_vec_fourier, H0, K);
	auto h1n = ConvHoriz(src_vec_fourier, H1, K);

	h0n = IPL::PryDown(h0n);
	h1n = IPL::PryDown(h1n);

	h0n = IPL::PryUp(h0n);
	h1n = IPL::PryUp(h1n);

	h0n = ConvHoriz(h0n, G0, K);
	h1n = ConvHoriz(h1n, G1, K);

	auto res_fourier = Vec2DAdd(h0n, h1n);

	auto res_complex = IPL::Fourier::IFFT(res_fourier);

	int rows = res_complex.size();
	int cols = res_complex[0].size();

	cv::Mat dst(rows, cols, CV_64FC1);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			double tmp = std::abs(res_complex[i][j]);
			dst.at<double>(i, j) = tmp;
		}
	}

	normalize(dst, dst, 0, 1, NORM_MINMAX);
	imshow("dst", dst);

	//imshow("res", IPL::VectorComplex2D2Mat(res_complex));
	
	/*imshow("h0n", IPL::NormalizeVec2DToMat(h0n));
	imshow("h1n", IPL::NormalizeVec2DToMat(h1n));
	imshow("res", IPL::NormalizeVec2DToMat(res));
	imshow("src", IPL::NormalizeVec2DToMat(src_vec));*/





	//////////////////////////////////////////////////////////////////////////

	//Mat src = imread("../data/DIP3E_Original_Images_CH07/vase.tif", 0);
	////resize(src, src, { 512,512 });
	////imshow("src", IPL::NormalizeVec2DToMat(IPL::Mat2Vector2D(src)));

	//Vec2D a_lv3, b_lv3, c_lv3, d_lv3;
	//SubbandCode(IPL::Mat2Vector2D(src), a_lv3, b_lv3, c_lv3, d_lv3);
	///*imshow("b_lv3", b_lv3);
	//imshow("c_lv3", c_lv3);
	//imshow("d_lv3", d_lv3);*/

	//Vec2D a_lv2, b_lv2, c_lv2, d_lv2;
	//SubbandCode(a_lv3, a_lv2, b_lv2, c_lv2, d_lv2);
	///*imshow("b_lv2", b_lv2);
	//imshow("c_lv2", c_lv2);
	//imshow("d_lv2", d_lv2);*/

	//Vec2D a_lv1, b_lv1, c_lv1, d_lv1;
	//SubbandCode(a_lv2, a_lv1, b_lv1, c_lv1, d_lv1);
	///*imshow("a_lv1", a_lv1);
	//imshow("b_lv1", b_lv1);
	//imshow("c_lv1", c_lv1);
	//imshow("d_lv1", d_lv1);*/


	//// 重建
	//imshow("b", IPL::NormalizeVec2DToMat(a_lv1));

	//auto a = IPL::PryUpByCol(a_lv1);
	//auto a_back = ConvVert(a, G0, K);

	//auto b = IPL::PryUpByCol(b_lv1);
	//auto b_back = ConvVert(b, G1, K);

	//auto c = IPL::PryUpByCol(c_lv1);
	//auto c_back = ConvVert(c, G0, K);

	//auto d = IPL::PryUpByCol(d_lv1);
	//auto d_back = ConvVert(d, G1, K);

	//auto a_b = Vec2DAdd(a, b);
	//auto c_d = Vec2DAdd(c, d);

	//auto ab = IPL::PryUpByRow(a_b);
	//auto ab_back = ConvHoriz(ab, G0, K);

	//auto cd = IPL::PryUpByRow(c_d);
	//auto cd_back = ConvHoriz(cd, G1, K);

	//auto c_res = Vec2DAdd(ab, cd);

	//imshow("c", IPL::NormalizeVec2DToMat(c_res));



	waitKey();
	return 0;


}

int K = 8;
//int K = 2;
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

	/*static std::vector<double> table = {
		1.0 / sqrt(2.0),
		1.0 / sqrt(2.0)
	};*/

	return table[n];
}

void SubbandCode(const Vec2D &src, Vec2D &dst_a, Vec2D &dst_dV, Vec2D &dst_dH, Vec2D &dst_dD)
{
	auto src_vec = src;

	auto h0m = ConvHoriz(src_vec, H0, K);
	h0m = IPL::PryDownByRow(h0m);
	auto h0n = ConvVert(h0m, H0, K);
	h0n = IPL::PryDownByCol(h0n);
	auto a = IPL::NormalizeVec2DToMat(h0n);
	dst_a = h0n;

	auto h1n = ConvVert(h0m, H1, K);
	h1n = IPL::PryDownByCol(h1n);
	auto b = IPL::NormalizeVec2DToMat(h1n);
	cv::equalizeHist(b, b);
	dst_dV = h1n;

	auto h1m = ConvHoriz(src_vec, H1, K);
	h1m = IPL::PryDownByRow(h1m);
	h0n = ConvVert(h1m, H0, K);
	h0n = IPL::PryDownByCol(h0n);
	auto c = IPL::NormalizeVec2DToMat(h0n);
	cv::equalizeHist(c, c);
	dst_dH = h0n;

	h1n = ConvVert(h1m, H1, K);
	h1n = IPL::PryDownByCol(h1n);
	auto d = IPL::NormalizeVec2DToMat(h1n);
	cv::equalizeHist(d, d);
	dst_dD = h1n;

	
}
//
//resize(src, src, { 512,512 });
//
//auto src_vec = IPL::Mat2Vector2D(src);
//
//std::vector<std::vector<double>> approximate;
//std::vector<std::vector<double>> residual;
//IPL::PyramidExample(src_vec, approximate, residual);
//auto a_8 = IPL::NormalizeVec2DToMat(approximate);//近似值
//auto b_9 = IPL::NormalizeVec2DToMat(residual);// 残差值
//
//// 还原第五级
//auto approximate_up = IPL::NearestNeighborInterpolation(approximate,
//	approximate.size() * 2, approximate[0].size() * 2);
//auto res = approximate_up;
//for (int i = 0; i < approximate_up.size(); i++)
//{
//	for (int j = 0; j < approximate_up[0].size(); j++)
//	{
//		res[i][j] = approximate_up[i][j] + residual[i][j];
//	}
//}
//auto res_mat = IPL::NormalizeVec2DToMat(res);
//imshow("res_mat", res_mat);
//imshow("src", IPL::NormalizeVec2DToMat(src_vec));
//imshow("residual", b_9);
//imshow("approximate", a_8);





