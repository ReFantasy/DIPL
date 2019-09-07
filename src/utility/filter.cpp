#include "filter.h"

namespace IPL
{
	cv::Mat FourierFilter::operator()(const Mat &src, const vector<vector<double>> &gauss, int ft_type)
	{
		assert(src.type() == CV_8UC1);

		// FFT
		if (ft_type == 0)
		{

			int rows = src.rows;
			int cols = src.cols;
			auto src_data = ImageData(src);

			// 傅里叶变换
			_src_fourier_res = fourier.FFT(src_data);

			// 频率域滤波
			_dst_fourier_res = filter(_src_fourier_res, gauss);

			// 返回空间域
			auto _dst_data = fourier.IFFT(_dst_fourier_res);

			// 输出图像
			auto dst_image_data = ConvertToImage(_dst_data);
			auto res =  Out8UC1(dst_image_data);

			return res;
		}
		// DFT
		else
		{
			int rows = src.rows;
			int cols = src.cols;
			auto src_data = ImageData(src);

			// 傅里叶变换
			_src_fourier_res = fourier.DFT(src_data);

			// 频率域滤波
			_dst_fourier_res = filter(_src_fourier_res, gauss);

			// 返回空间域
			auto _dst_data = fourier.IDFT(_dst_fourier_res);

			// 输出图像
			auto dst_image_data = ConvertToImage(_dst_data);
			return Out8UC1(dst_image_data);
		}

	}

	vector<vector<double>> FourierFilter::ImageData(const Mat &img)
	{
		vector<vector<double>> src_data(img.rows, vector<double>(img.cols, 0));
		for (int i = 0; i < img.rows; i++)
		{
			for (int j = 0; j < img.cols; j++)
			{
				src_data[i][j] = img.data[i*img.cols + j] * pow(-1, i + j);
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
				dst.data[i*cols + j] = tmp;
			}
		}

		return dst;
	}


	vector<vector<std::complex<double>>> FourierFilter::filter(const vector<vector<std::complex<double>>> &fourier,
		const vector<vector<double>> &gauss)
	{
		int rows = fourier.size();
		int cols = fourier[0].size();

		vector<vector<std::complex<double>>> tmp(rows, vector<std::complex<double>>(cols, 0));

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				tmp[i][j] = gauss[i][j] * fourier[i][j];
			}
		}

		return tmp;
	
	}

	cv::Mat NormalizeVec2DToMat(const vector<vector<double>> &vec2d)
	{
		assert(vec2d.size() > 0);
		assert(vec2d[0].size());
		int rows = vec2d.size();
		int cols = vec2d[0].size();
		cv::Mat dst(rows, cols, CV_64FC1);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{

				dst.at<double>(i, j) = vec2d[i][j];
			}
		}
		normalize(dst, dst, 0, 1, NORM_MINMAX);
		dst.convertTo(dst, CV_8UC1, 255);
		return dst;
	}

	cv::Mat MeanBlurArithmetic(const cv::Mat &_src, int kern_size)
	{
		auto src = IPL::Mat2Vector2D(_src);
		auto _blur = MeanBlurArithmetic(src, kern_size);
		return NormalizeVec2DToMat(_blur);
	}
	
	cv::Mat MeanBlurGeometry(const cv::Mat &_src, int kern_size)
	{
		auto src = IPL::Mat2Vector2D(_src);
		auto _blur = MeanBlurGeometry(src, kern_size);
		return NormalizeVec2DToMat(_blur);
	}

	cv::Mat MeanBlurHarmonic(const Mat &_src, int kern_size)
	{
		auto src = IPL::Mat2Vector2D(_src);
		auto _blur = MeanBlurHarmonic(src, kern_size);
		return NormalizeVec2DToMat(_blur);
	}

	cv::Mat MeanBlurInverseHarmonic(const Mat &_src, int kern_size, double Q)
	{
		auto src = IPL::Mat2Vector2D(_src);
		auto _blur = MeanBlurInverseHarmonic(src, kern_size, Q);
		return NormalizeVec2DToMat(_blur);
	}

}

