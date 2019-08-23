#include <iostream>      
#include <vector>
#include <iterator>
#include <random>
#include <chrono>
#include "opencv2/opencv.hpp"
#include "algorithm/Fourier.h"
#include "image/Image.h"
#include "Rand.h"
#include <share.h>
#include "Timer.h"


using namespace std;
using namespace cv;

template<typename T>
void Print(const vector<vector<T>> &vt)
{
	for (const auto &e : vt)
	{
		for (const auto&i : e)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
}
std::ostream& operator<<(std::ostream &os, const std::complex<double> &cd)
{
	os << "[" << cd.real() << "," << cd.imag() << "]";
	return os;
}

int OpencvFourier(Mat img);
int MyFourier(Mat image);

//std::vector<std::complex<double>> _FFT(const std::vector<std::complex<double>> &in)
//{
//	std::vector<std::complex<double>> out(in.size(), std::complex<double>{0,0});
//
//	int K = in.size() / 2;
//	if (K > 1)
//	{
//		std::vector<std::complex<double>> even(K, std::complex<double>{0,0});
//		std::vector<std::complex<double>> odd(K, std::complex<double>{0, 0});
//		for (int i = 0; i < in.size(); i += 2)
//		{
//			even[i / 2] = in[i];
//			odd[i / 2] = in[i + 1];
//		}
//
//		auto even_fourier = std::move(_FFT(even));
//		auto odd_fourier = std::move(_FFT(odd));
//
//
//
//		std::vector<std::complex<double>> W_2k_u(K, std::complex<double>{0, 0});
//		for (int i = 0; i < K; i++)
//		{
//			IPL::Eulerform e(1, -2.0*PI*i / 2 / K);
//			W_2k_u[i] = odd_fourier[i] * e.GetComplex();
//		}
//
//		for (int i = 0; i < K; i++)
//		{
//			out[i] = even_fourier[i] + W_2k_u[i];
//		}
//		for (int i = 0; i < K; i++)
//		{
//			out[i + K] = even_fourier[i] - W_2k_u[i];
//		}
//	}
//	else
//	{
//		assert(K == 1);
//		std::complex<double> even0 = in[0];
//		std::complex<double> odd0 = in[1];
//		out[0] = even0 + odd0;
//		out[1] = even0 - odd0;
//	}
//
//	return out;
//}




int main()
{
	Timer timer;
	IPL::Fourier fourier;
	Rand<double> _rand(1, 10);

	//Mat src = imread("6.tif", 0);
	//vector<vector<double>> vec_src(src.rows, vector<double>(src.cols, 0));
	//for (int i = 0; i < src.rows; i++)
	//	for (int j = 0; j < src.cols; j++)
	//		vec_src[i][j] = src.data[i*src.cols + j];

	//// geneate filter kernel
	//auto kernel = IPL::GHPF(src.rows, src.cols, 160);

	//IPL::Filter filter;
	//filter.SetKernel(kernel);
	//IPL::FourierFilter fourier_filter;
	//
	//Mat dst = fourier_filter(src, filter);

	//
	//imshow("dst", dst);

	int n = 512;
	vector<vector<complex<double>>> In(n, vector<complex<double>>(n, complex<double>(0,0)));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			In[i][j]._Val[0] = _rand();
			In[i][j]._Val[1] = _rand();
		}
	}
	


	auto out = In;

	timer.ReSet();
	out = fourier.FFT(In);
	cout << timer.Elapse() << endl;
	//Print(out);

	cout << endl<<"-----------------------" << endl;

	timer.Start();
	auto res = fourier.DFT(In);
	cout << timer.Elapse() << endl;
	//Print(res);



	
	

	
	waitKey();
	system("pause");
	return 0;
}

int MyFourier(Mat image)
{
	Mat src;
	cvtColor(image, src, CV_BGR2GRAY);
	int rows = src.rows;
	int cols = src.cols;
	vector<vector<double>> img(rows, vector<double>(cols, 0));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			img[i][j] = src.data[i*cols + j] * pow(-1, i + j);
		}
	}

	IPL::Fourier fourier;
	auto dft_img = fourier.DFT(img);

	// 频谱
	Mat dst(rows, cols, CV_32FC1);
	vector<vector<double>> pu(rows, vector<double>(cols, 0));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			pu[i][j] = std::abs(dft_img[i][j]);

		}
	}


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			double tmp = 1 + log(abs(pu[i][j]));
			if (tmp > 255)
				tmp = 255;
			if (tmp < 0)
				tmp = 0;
			pu[i][j] = tmp;
		}
	}

	// 归一化
	double minv = 0;
	double maxv = 0;
	for (auto&e : pu)
		for (auto &i : e)
		{
			maxv = (i > maxv ? i : maxv);
			minv = (minv < i ? minv : i);
		}
	for (auto&e : pu)
		for (auto &i : e)
		{
			i -= minv;
		}
	for (auto&e : pu)
		for (auto &i : e)
		{
			i /= (maxv - minv);
			i *= 255;
		}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			src.data[i*cols + j] = pu[i][j];
		}
	}

	imshow("MyFourier", src);
	waitKey(1);
	return 0;
}

int OpencvFourier(Mat img)
{
	Mat src = img;
	if (src.empty())
	{
		return -1;
	}

	Mat src_gray;
	cvtColor(src, src_gray, CV_RGB2GRAY);//灰度图像做傅里叶变换

	int m = getOptimalDFTSize(src_gray.rows);//2,3,5的倍数有更高效率的傅里叶转换
	int n = getOptimalDFTSize(src_gray.cols);

	Mat dst;
	///把灰度图像放在左上角，在右边和下边扩展图像，扩展部分填充为0；
	copyMakeBorder(src_gray, dst, 0, m - src_gray.rows, 0, n - src_gray.cols, BORDER_CONSTANT, Scalar::all(0));
	cout << dst.size() << endl;

	//新建一个两页的array，其中第一页用扩展后的图像初始化，第二页初始化为0
	Mat planes[] = { Mat_<float>(dst), Mat::zeros(dst.size(), CV_32F) };
	Mat  completeI;
	merge(planes, 2, completeI);//把两页合成一个2通道的mat

	//对上边合成的mat进行傅里叶变换，支持原地操作，傅里叶变换结果为复数。通道1存的是实部，通道2存的是虚部。
	dft(completeI, completeI);

	split(completeI, planes);//把变换后的结果分割到各个数组的两页中，方便后续操作
	magnitude(planes[0], planes[1], planes[0]);//求傅里叶变换各频率的幅值，幅值放在第一页中。

	Mat magI = planes[0];
	//傅立叶变换的幅度值范围大到不适合在屏幕上显示。高值在屏幕上显示为白点，
	//而低值为黑点，高低值的变化无法有效分辨。为了在屏幕上凸显出高低变化的连续性，我们可以用对数尺度来替换线性尺度:
	magI += 1;
	log(magI, magI);//取对数
	magI = magI(Rect(0, 0, src_gray.cols, src_gray.rows));//前边对原始图像进行了扩展，这里把对原始图像傅里叶变换取出，剔除扩展部分。


	//这一步的目的仍然是为了显示。 现在我们有了重分布后的幅度图，
	//但是幅度值仍然超过可显示范围[0,1] 。我们使用 normalize() 函数将幅度归一化到可显示范围。
	normalize(magI, magI, 0, 1, CV_MINMAX);//傅里叶图像进行归一化。


	//重新分配象限，使（0,0）移动到图像中心，
	//在《数字图像处理》中，傅里叶变换之前要对源图像乘以（-1）^(x+y)进行中心化。
	//这是是对傅里叶变换结果进行中心化
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat tmp;
	Mat q0(magI, Rect(0, 0, cx, cy));
	Mat q1(magI, Rect(cx, 0, cx, cy));
	Mat q2(magI, Rect(0, cy, cx, cy));
	Mat q3(magI, Rect(cx, cy, cx, cy));


	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);



	namedWindow("InputImage");
	imshow("InputImage", src);

	namedWindow("SpectrumImage");
	imshow("SpectrumImage", magI);
}