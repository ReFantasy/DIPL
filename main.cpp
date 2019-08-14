#include <iostream>
#include "opencv2/opencv.hpp"
#include "Fourier.h"
#include <iomanip>
#include <ctime>
using namespace std;
using namespace cv;


template<typename T>
void Print(const vector<vector<T>> &ary)
{
	int M = ary.size();
	int N = ary[0].size();

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << ary[i][j] << "  ";
		}
		cout << endl;
	}
}

template<typename T>
ostream& operator<<(ostream &os, const complex<T> &cl)
{
	printf("(%4.2f,%4.2f)", cl.real(), cl.imag());
	return os;
}

int main(int argc, char *argv[])
{
	

	

	system("pause");
	return 0;
}




//Fourier fourier;
//vector<double> input = { 1.5,2.3,4.7,4.1 };
//auto res = fourier.DFT(input);
//
//for (int i = 0; i < res.size(); i++)
//{
//	//cout << i << " : " << res[i].real() << "  " << res[i].imag() << endl;
//	printf("%d : %.4f  %.4f\n", i, res[i].real(), res[i].imag());
//}
//
//cout << "逆变换" << endl;
//std::vector<std::complex<double>> ires_midea;
//auto ires = fourier.IDFT(res, &ires_midea);
//for (int i = 0; i < ires.size(); i++)
//{
//	cout << ires[i] << endl;
//}
//
//cout << "逆变换中间过程数据" << endl;
//for (int i = 0; i < ires_midea.size(); i++)
//{
//	//cout << i << " : " << res[i].real() << "  " << res[i].imag() << endl;
//	printf("%d : %.4f  %.4f\n", i, ires_midea[i].real(), ires_midea[i].imag());
//}

//
//srand(time(0));
//cout << "opencv dft" << endl;
//Mat src(3, 3, CV_64FC1);
//for (int i = 0; i < src.rows; i++)
//{
//	for (int j = 0; j < src.cols; j++)
//	{
//		src.at<double>(i, j) = rand() % 100;
//	}
//}
//
//cout << src << endl << endl;;
//
//Mat dst;
//dft(src, dst, DFT_COMPLEX_OUTPUT);
//cout << dst << endl;
//
//cout << endl << endl;
//
//cout << "my dft" << endl;
//Fourier fourier;
//vector<vector<double>> a(src.rows, vector<double>(src.cols, 0));
//for (int i = 0; i < src.rows; i++)
//{
//	for (int j = 0; j < src.cols; j++)
//	{
//		a[i][j] = src.at<double>(i, j);
//	}
//}
//
//cout << "初始数据" << endl;
//Print(a);
//cout << endl;
//
//cout << "傅里叶变换的结果" << endl;
//auto res = fourier.DFT(a);
//Print(res);
//cout << endl;
//
//cout << "傅里叶逆变换的结果" << endl;
//auto ires = fourier.IDFT(res);
//Print(ires);
//cout << endl;