#include "Image.h"

#include "Image.h"

cv::Mat FourierFilter::operator()(const Mat &src, std::function<Complex2D(Complex2D)> op)
{
	assert(src.type() == CV_8UC1);

	int rows = src.rows;
	int cols = src.cols;
	auto src_data = ImageData(src);

	// ∏µ¿Ô“∂±‰ªª
	_src_fourier_res = fourier.DFT(src_data);

	// ∆µ¬ ”Ú¬À≤®
	_dst_fourier_res = op(_src_fourier_res);

	// ∑µªÿø’º‰”Ú
	auto _dst_data = fourier.IDFT(_dst_fourier_res);

	//  ‰≥ˆÕºœÒ
	auto dst_image_data = ConvertToImage(_dst_data);
	return Out8UC1(dst_image_data);

}

vector<vector<double>> FourierFilter::ImageData(const Mat &img)
{
	vector<vector<double>> src_data(img.rows, vector<double>(img.cols, 0));
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			src_data[i][j] = img.data[i*img.cols + j]*pow(-1, i+j);
		}
	}

	return src_data;
}

vector<vector<double>> FourierFilter::ConvertToImage(const Complex2D &dst_fourier)
{
	int rows = dst_fourier.size();
	int cols = dst_fourier[0].size();

	vector<vector<double>> dst_data(rows, vector<double>(cols, 0));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			dst_data[i][j] = dst_fourier[i][j].real()*pow(-1, i + j);
		}
	}

	return dst_data;
}

cv::Mat FourierFilter::Out8UC1(const vector<vector<double>> &d)
{
	int rows = d.size();
	int cols = d[0].size();

	Mat dst(rows, cols, CV_8UC1);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			double tmp = 0;

			tmp = d[i][j];
			tmp = (tmp > 255 ? 255 : tmp);
			tmp = (tmp < 0 ? 0 : tmp);
			dst.data[i*cols+j] =tmp;
		}
	}

	return dst;
}

Gauss::Gauss(int rows, int cols, double A, double sigma_x, double sigma_y)
{
	_gauss_array = GenGaussianKernel(rows, cols, A, sigma_x, sigma_y);
}

void Gauss::SetKernel(const vector<vector<double>> &gauss_array)
{
	_gauss_array = gauss_array;
}

vector<vector<std::complex<double>>> Gauss::operator()(const vector<vector<std::complex<double>>> &fourier)
{
	int rows = fourier.size();
	int cols = fourier[0].size();

	vector<vector<std::complex<double>>> tmp(rows, vector<std::complex<double>>(cols, 0));

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			tmp[i][j] = _gauss_array[i][j] * fourier[i][j];
		}
	}

	return tmp;
}

