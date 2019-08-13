#include "histogram.h"


std::vector<int> GetHistogram(const Mat &gray_image, int L )
{
	assert(gray_image.type() == CV_8UC1);

	vector<int> table(L, 0);

	for (int i = 0; i < gray_image.rows*gray_image.cols; i++)
	{
		table[gray_image.data[i]]++;
	}

	return table;
}

void ShowHistogram(std::string name, const Mat &gray_image, int Height)
{
	std::vector<int> histogram = GetHistogram(gray_image);

	auto it = std::max_element(histogram.begin(), histogram.end());

	std::vector<double> histogram_d;
	for (int i = 0; i < histogram.size(); i++)
	{
		histogram_d.push_back(histogram[i] / (double)(*it));
	}

	Mat histogram_img(histogram.size(), Height, CV_8UC1, Scalar(255));

	for (int j = 0; j < histogram.size(); j++)
	{
		line(histogram_img, Point(j,Height-1), Point(j, Height - 1-histogram_d[j]*Height), Scalar(0));
		
	}

	imshow(name, histogram_img);
}
