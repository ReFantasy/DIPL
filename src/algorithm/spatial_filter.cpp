#include "spatial_filter.h"
#include <cassert>

//std::vector<std::vector<double>> IPL::MedianBlur(const std::vector<std::vector<double>> src, KernelSize<int> kern_sz)
//{
//	assert(src.size() > 0);
//	assert(src[0].size() > 0);
//	int rows = src.size();
//	int cols = src[0].size();
//
//	int half_x = (kern_sz.x - 1) / 2;
//	int half_y = (kern_sz.y - 1) / 2;
//
//	for (int i = half_x; i < rows - half_x; i++)
//	{
//		for (int j = half_y; j < cols - half_y; j++)
//		{
//
//		}
//	}
//
//}

std::vector<std::vector<double>> IPL::PaddingImage(const std::vector<std::vector<double>> &src, int left, int right, int top, int bottom)
{
	assert(src.size() > 0);
	assert(src[0].size() > 0);
	int old_rows = src.size();
	int old_cols = src[0].size();
	int new_rows = old_rows + top + bottom;
	int new_cols = old_cols + left + right;

	std::vector<std::vector<double>> new_image(new_rows, std::vector<double>(new_cols, 0));

	// ����ԭʼ����
	for (int i = 0; i < old_rows; i++)
	{
		for (int j = 0; j < old_cols; j++)
		{
			new_image[i + top][j + left] = src[i][j];
		}
	}

	// �����Ե
	for (int i = 0; i < old_rows; i++)
	{
		// left
		for (int j = 0; j < left; j++)
		{
			new_image[i + top][j] = src[i][0];
		}
		//right
		for (int j = 0; j < right; j++)
		{
			new_image[i + top][j + left + old_cols] = src[i][old_cols - 1];
		}
	}

	for (int j = 0; j < new_cols; j++)
	{
		for (int i = 0; i < top; i++)
		{
			new_image[i][j] = new_image[top][j];
		}
		for (int i = 0; i < bottom; i++)
		{
			new_image[i+top+old_rows][j] = new_image[old_rows-1][j];
		}
	}

	return new_image;
}


std::vector<std::vector<double>> IPL::PaddingImage(const std::vector<std::vector<double>> &src, int n)
{
	return PaddingImage(src, n, n, n, n);
}

std::vector<std::vector<double>> IPL::MeanBlurArithmetic(const std::vector<std::vector<double>> &src, int kern_size)
{
	// �ж��˲��˴�С�Ƿ�Ϊ����
	if (!IsOdd(kern_size))
		kern_size += 1;

	// ��չͼ��߽�
	int half_kern = (kern_size - 1) / 2;
	auto image_padded = PaddingImage(src, half_kern);

	// ��ֵ�˲�
	int rows = src.size();
	int cols = src[0].size();
	std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));

	for (int i = half_kern; i < rows+ half_kern; i++)
	{
		for (int j = half_kern; j < cols+ half_kern; j++)
		{
			double tmp = 0;
			for (int m = i-half_kern; m < i + half_kern; m++)
			{
				for (int n = j-half_kern; n < j + half_kern; n++)
				{
					tmp += image_padded[m][n];
				}
			}

			tmp /= (kern_size*kern_size);
			dst[i - half_kern][j - half_kern] = tmp;
		}
	}
	return dst;
}

std::vector<std::vector<double>> IPL::MeanBlurGeometry(const std::vector<std::vector<double>> &src, int kern_size)
{
	// �ж��˲��˴�С�Ƿ�Ϊ����
	if (!IsOdd(kern_size))
		kern_size += 1;

	// ��չͼ��߽�
	int half_kern = (kern_size - 1) / 2;
	auto image_padded = PaddingImage(src, half_kern);

	// ��ֵ�˲�
	int rows = src.size();
	int cols = src[0].size();
	std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));

	for (int i = half_kern; i < rows + half_kern; i++)
	{
		for (int j = half_kern; j < cols + half_kern; j++)
		{
			double tmp = 1;
			for (int m = i - half_kern; m < i + half_kern; m++)
			{
				for (int n = j - half_kern; n < j + half_kern; n++)
				{
					tmp *= image_padded[m][n];
				}
			}

			tmp = pow(tmp, 1.0 / (kern_size * kern_size));
			dst[i - half_kern][j - half_kern] = tmp;
		}
	}
	return dst;
}

std::vector<std::vector<double>> IPL::MeanBlurHarmonic(const std::vector<std::vector<double>> &src, int kern_size)
{
	// �ж��˲��˴�С�Ƿ�Ϊ����
	if (!IsOdd(kern_size))
		kern_size += 1;

	// ��չͼ��߽�
	int half_kern = (kern_size - 1) / 2;
	auto image_padded = PaddingImage(src, half_kern);

	// ��ֵ�˲�
	int rows = src.size();
	int cols = src[0].size();
	std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));

	for (int i = half_kern; i < rows + half_kern; i++)
	{
		for (int j = half_kern; j < cols + half_kern; j++)
		{
			double tmp = 0;
			for (int m = i - half_kern; m < i + half_kern; m++)
			{
				for (int n = j - half_kern; n < j + half_kern; n++)
				{
					tmp += 1.0 / image_padded[m][n];
				}
			}

			tmp = kern_size * kern_size / tmp;
			dst[i - half_kern][j - half_kern] = tmp;
		}
	}
	return dst;
}

std::vector<std::vector<double>> IPL::MeanBlurInverseHarmonic(const std::vector<std::vector<double>> &src, int kern_size, double Q)
{
	// �ж��˲��˴�С�Ƿ�Ϊ����
	if (!IsOdd(kern_size))
		kern_size += 1;

	// ��չͼ��߽�
	int half_kern = (kern_size - 1) / 2;
	auto image_padded = PaddingImage(src, half_kern);

	// ��ֵ�˲�
	int rows = src.size();
	int cols = src[0].size();
	std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));

	for (int i = half_kern; i < rows + half_kern; i++)
	{
		for (int j = half_kern; j < cols + half_kern; j++)
		{
			double tmp1 = 0;
			double tmp2 = 0;
			for (int m = i - half_kern; m < i + half_kern; m++)
			{
				for (int n = j - half_kern; n < j + half_kern; n++)
				{
					tmp1 += pow(image_padded[m][n], Q + 1);
					tmp2 += pow(image_padded[m][n], Q);
				}
			}

			
			dst[i - half_kern][j - half_kern] = tmp1 / tmp2;
		}
	}
	return dst;
}

bool IPL::IsOdd(int num)
{
	return (num % 2);
}


