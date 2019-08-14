#include <iostream>
#include "opencv2/opencv.hpp"
#include "Fourier.h"
using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
	Mat src = imread("C:\\Users\\30974\\Desktop\\flower.jpg", 0);

	Fourier fourier;
	vector<double> input = {1.5,2.3,4.7,4.1};
	auto res = fourier.DFT(input);

	for (int i = 0; i < res.size(); i++)
	{
		//cout << i << " : " << res[i].real() << "  " << res[i].imag() << endl;
		printf("%d : %.4f  %.4f\n", i, res[i].real(), res[i].imag());
	}

	cout << "逆变换" << endl;
	std::vector<std::complex<double>> ires_midea;
	auto ires = fourier.IDFT(res, &ires_midea);
	for (int i = 0; i < ires.size(); i++)
	{
		cout << ires[i] << endl;
	}

	cout << "逆变换中间过程数据" << endl;
	for (int i = 0; i < ires_midea.size(); i++)
	{
		//cout << i << " : " << res[i].real() << "  " << res[i].imag() << endl;
		printf("%d : %.4f  %.4f\n", i, ires_midea[i].real(), ires_midea[i].imag());
	}
	system("pause");
	return 0;
}