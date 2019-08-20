/************************************************************************
 *
 *  自定义图像类型与OpenCV图像类型转换
 *
 ***********************************************************************/
#ifndef __IMAGE_H__
#define __IMAGE_H__
#include <vector>
#include <string>
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

class Image
{
public:
	Image(vector<vector<double>> data) :_data(data) {}

	Image(const Image &img)
	{
		_data = img._data;
	}
	Image(Image &&img)
	{
		_data = std::move(img._data);
	}
	Image& operator=(const Image &img)
	{
		_data = img._data;
	}
	Image& operator=(Image &&img)
	{
		_data = std::move(img._data);
	}
	~Image() {}

	vector<double>& operator[](int index);
	const vector<double>& operator[](int index)const;

	int Rows()const;
	int Cols()const;

	vector<vector<double>>& GetData() { return _data; }

	const vector<vector<double>>& GetData()const { return _data; }
private:
	vector<vector<double>> _data;

};

Image Mat2Image(const Mat &img);

Mat Image2Mat(const Image &image, int image_type);

Image ReadImage(const string name);
void ShowImage(const string &name,const Image &img, bool is_normalized = false);



#endif//__IMAGE_H__