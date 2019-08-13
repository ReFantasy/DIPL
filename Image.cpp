#include "Image.h"
#include "opencv2/opencv.hpp"
#include <algorithm>


int Image::Rows() const
{
	return data.size();
}

int Image::Cols() const
{
	if (Rows())
	{
		return data[0].size();
	}
	else
	{
		return 0;
	}
}

bool Image::SetValue(int r, int c, double v)
{
	if (r >= Rows() || c >= Cols())
		return false;

	data[r][c] = v;
	return true;
}

bool Image::GetValue(int r, int c, double &v) const
{
	if (r >= Rows() || c >= Cols())
		return false;
	v = data[r][c];
	return true;
}

void Image::calibrate()
{
	double minv;
	double maxv;
	double smaxv;
	if (_ty == ImageType::DOUBLE)
	{
		smaxv = 1;
	}
	else if(_ty==ImageType::UCHAR)
	{
		smaxv = 255;
	}

	minv = MinValue();
	for (int i = 0; i < Rows(); i++)
	{
		for (int j = 0; j < Cols(); j++)
		{
			data[i][j] -= minv;
		}
	}

	maxv = MaxValue();
	for (int i = 0; i < Rows(); i++)
	{
		for (int j = 0; j < Cols(); j++)
		{
			data[i][j] /= maxv;
		}
	}

	for (int i = 0; i < Rows(); i++)
	{
		for (int j = 0; j < Cols(); j++)
		{
			data[i][j] *= smaxv;
		}
	}

}

double Image::MinValue() const
{
	double minv = 0;
	/*for (const auto&e : data)
	{
		auto it = std::min_element(e.begin(), e.end());
		minv = (minv < *it ? minv : *it);
	}*/

	for (int i = 0; i < Rows(); i++)
	{
		for (int j = 0; j < Cols(); j++)
		{
			minv = (minv < data[i][j] ? minv : data[i][j]);
		}
	}


	return minv;
}

double Image::MaxValue() const
{
	double maxv = 0;
	/*for (const auto&e : data)
	{
		auto it = std::min_element(e.begin(), e.end());
		maxv = (maxv < *it ? *it : maxv);
	}*/

	for (int i = 0; i < Rows(); i++)
	{
		for (int j = 0; j < Cols(); j++)
		{
			maxv = (maxv < data[i][j] ? data[i][j] : maxv);
		}
	}

	return maxv;
}

std::vector<double>& Image::operator[](size_t index)
{
	return data[index];
}

const std::vector<double>& Image::operator[](size_t index) const
{
	return data[index];
}

Image CreateImage(const cv::Mat &mat)
{
	Image img;
	img._ty = ImageType::UCHAR;

	int rows = mat.rows;
	int cols = mat.cols;
	img.data = std::vector<std::vector<double>>(rows, std::vector<double>(cols, 0));

	switch (mat.type())
	{
	case CV_8UC1:
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				img.data[i][j] = mat.data[i*cols + j];
			}
		}
		img._ty = ImageType::UCHAR;
		break;

	case CV_32FC1:
	case CV_64FC1:
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				img.data[i][j] = mat.at<float>(i,j);
			}
		}
		img._ty = ImageType::DOUBLE;
		break;

	default:
		break;
	}

	return img;
}

cv::Mat GetMatFromImage(const Image &img)
{
	int rows = img.Rows();
	int cols = img.Cols();

	cv::Mat mat;
	if (img._ty == ImageType::UCHAR)
	{
		mat.create(rows, cols, CV_8UC1);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				mat.data[i*cols+j] = img[i][j];
			}
		}

	}
	else if (img._ty == ImageType::DOUBLE)
	{
		mat.create(rows, cols, CV_32FC1);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				mat.at<float>(i,j) = img[i][j];
			}
		}
	}
	else
	{
		mat.create(0, 0, CV_8UC1);
	}


	

	return mat;
}

Image operator-(const Image &lhs, const Image &rhs)
{
	if (lhs.Rows() != rhs.Rows() || lhs.Cols() != rhs.Cols())
	{
		throw - 1;
	}

	Image res = lhs;

	for (int i = 0; i < res.Rows(); i++)
	{
		for (int j = 0; j < res.Cols(); j++)
		{
			res[i][j] -= rhs[i][j];
		}
	}
	return res;
}
