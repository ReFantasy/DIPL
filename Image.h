#ifndef __IMAGE_H__
#define __IMAGE_H__
#include <vector>

namespace cv
{
	class Mat;
}


enum class ImageType
{
	DOUBLE,UCHAR
};

class Image
{
	friend Image CreateImage(const cv::Mat &mt);
	friend cv::Mat GetMatFromImage(const Image &img);
public:
	Image() = default;
	~Image() {};

public:
	std::vector<double>& operator[](size_t index);
	const std::vector<double>& operator[](size_t index)const;
	
public:
	int Rows()const;
	int Cols()const;
	bool SetValue(int r, int c, double v);
	bool GetValue(int r, int c, double &v)const;
	void calibrate();
	double MinValue()const;
	double MaxValue()const;
private:
	std::vector<std::vector<double>> data;
	ImageType _ty = ImageType::UCHAR;
};

Image CreateImage(const cv::Mat &mt);
cv::Mat GetMatFromImage(const Image &img);

Image operator-(const Image &lhs, const Image &rhs);
#endif//__IMAGE_H__

