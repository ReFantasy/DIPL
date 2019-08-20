#include "Image.h"

Image Mat2Image(const Mat &_img)
{
	Mat img;
	assert(_img.channels() == 1);

	if (_img.type() != CV_64FC1)
	{
		_img.convertTo(img, CV_64FC1, 1 / 255.0);
		img *= 255;
	}

	vector<vector<double>> v(img.rows, vector<double>(img.cols, 0));
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			double * p = (double*)(img.data);
			p += (i*img.cols + j);
			v[i][j] = *p;
		}
	}

	return v;
}

Mat Image2Mat(const Image &image, int image_type)
{
	Mat mat(image.Rows(), image.Cols(), CV_64FC1);
	for (int i = 0; i < image.Rows(); i++)
	{
		for (int j = 0; j < image.Cols(); j++)
		{
			double * p = (double*)(mat.data);
			p += (i*mat.cols + j);

			*p = image[i][j];
		}
	}

	return mat;
}

Image ReadImage(const string name)
{
	Mat img = imread(name, 0);
	return Mat2Image(img);
}

void ShowImage(const string &name, const Image &img, bool is_normalized )
{
	Mat mat(img.Rows(), img.Cols(), CV_8UC1);

	for (int i = 0; i < img.Rows(); i++)
	{
		for (int j = 0; j < img.Cols(); j++)
		{
			mat.data[i*img.Cols()+j] = std::round(img[i][j]);
		}
	}

	imshow(name, mat);
}

vector<double>& Image::operator[](int index)
{
	return _data[index];
}

const vector<double>& Image::operator[](int index) const
{
	return _data[index];
}

int Image::Rows() const
{
	if (_data.size() > 0)
	{
		return _data.size();
	}
	else
	{
		return 0;
	}
}

int Image::Cols() const
{
	if (Rows() > 0)
	{
		return _data[0].size();
	}
	else
	{
		return 0;
	}
}
