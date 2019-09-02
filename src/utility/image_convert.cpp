#include "image_convert.h"


//void IPL::ImageConvert(const std::vector<std::vector<double>> &vec_2d_double, cv::Mat &dst)
// {
//	 assert(vec_2d_double.size() > 0);;
//	 assert(vec_2d_double[0].size() > 0);
//	 int rows = vec_2d_double.size();
//	 int cols = vec_2d_double[0].size();
//
//	 dst = cv::Mat(rows, cols, CV_8UC1);
//
//	 for (int i = 0; i < rows; i++)
//	 {
//		 for (int j = 0; j < cols; j++)
//		 {
//			 double tmp = vec_2d_double[i][j];
//			 tmp = tmp > 255 ? 255 : tmp;
//			 tmp = tmp < 0 ? 0 : tmp;
//			 dst.data[i*cols + j] = tmp;
//		 }
//	 }
// }


//void IPL::ImageConvert(const std::vector<std::vector<std::complex<double>>> &vec_2d_complex, cv::Mat &dst)
// {
//	 assert(vec_2d_complex.size() > 0);;
//	 assert(vec_2d_complex[0].size() > 0);
//	 int rows = vec_2d_complex.size();
//	 int cols = vec_2d_complex[0].size();
//
//	 dst = cv::Mat(rows, cols, CV_8UC1);
//
//	 for (int i = 0; i < rows; i++)
//	 {
//		 for (int j = 0; j < cols; j++)
//		 {
//			 double tmp = vec_2d_complex[i][j].real();
//			 tmp = tmp > 255 ? 255 : tmp;
//			 tmp = tmp < 0 ? 0 : tmp;
//			 dst.data[i*cols + j] = tmp;
//		 }
//	 }
// }


std::vector<std::vector<double>> IPL::ImageConvert(const cv::Mat &mat)
{
	auto dst = std::vector<std::vector<double>>(mat.rows, std::vector<double>(mat.cols, 0));
	
	int rows = mat.rows;
	int cols = mat.cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			dst[i][j] = mat.data[i*cols + j];
		}
	}
	return dst;
}

//void IPL::ImageConvert(const cv::Mat &mat, std::vector<std::vector<std::complex<double>>> &dst)
//{
//	dst = std::vector<std::vector<std::complex<double>>>(mat.rows, std::vector<std::complex<double>>(mat.cols, { 0,0 }));
//
//	int rows = mat.rows;
//	int cols = mat.cols;
//
//	for (int i = 0; i < rows; i++)
//	{
//		for (int j = 0; j < cols; j++)
//		{
//			dst[i][j] = { mat.data[i*cols + j],0 };
//		}
//	}
//}

