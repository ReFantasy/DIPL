#include "Filter.h"



BoxFilter::BoxFilter()
{
}


BoxFilter::~BoxFilter()
{
}

Image Laplace::operator()(const Image &img)
{
	Image tmp = img;
	int rows = img.Rows();
	int cols = img.Cols();

	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			int t = img[i][j - 1] + img[i][j + 1] + img[i - 1][j] + img[i + 1][j] - 4 * img[i][j];
			tmp[i][j] = t;
			/*if (t > 255)t = 255;
			if (t < 0)t = 0;
			tmp[i][j] = t;*/
		}
	}

	/*for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			int t = img[i][j - 1] + img[i][j + 1] + img[i - 1][j] + img[i + 1][j] - 4 * img[i][j];
			if (t > 255)t = 255;
			if (t < 0)t = 0;
			tmp[i][j] = t;
		}
	}*/

	return tmp;
}
