#include "image_convert.h"




std::vector<std::vector<double>> IPL::Mat2Vector2D(const cv::Mat &mat)
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
std::vector<std::vector<double>> IPL::Mat2CentreVector2D(const cv::Mat &mat)
{
	auto dst = std::vector<std::vector<double>>(mat.rows, std::vector<double>(mat.cols, 0));

	int rows = mat.rows;
	int cols = mat.cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			dst[i][j] = mat.data[i*cols + j] * pow(-1, i + j);
		}
	}
	return dst;
}


