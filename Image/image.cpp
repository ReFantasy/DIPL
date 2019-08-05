#include "image.h"

IPL::Image::Image(int rows, int cols, PixType pix_type)
{
	switch (pix_type)
	{
	case IPL::NONE:
		break;

	case IPL::IPL_8UC1:
		_pointer_array = new Array2D<unsigned char>(rows, cols);
		_pix_type_size = sizeof(unsigned char);
		break;

	case IPL::IPL_64FC1:
		_pointer_array = new Array2D<double>(rows, cols);
		_pix_type_size = sizeof(double);
		break;

	default:
		break;
	}
	
}

IPL::Image::Image(const Image &img)
{
	_pointer_array->SetRows(img.Rows());
	_pointer_array->SetCols(img.Cols());
	memcpy(_pointer_array->Data(), img.Data(), img.Rows()*img.Cols()*img._pix_type_size);
}

IPL::Image::Image(Image &&img)
{
	_pointer_array->SetRows(img.Rows());
	_pointer_array->SetCols(img.Cols());
	_pointer_array->SetData(img.Data());

	img._pointer_array->SetRows(0);
	img._pointer_array->SetCols(0);
	img._pointer_array->SetData(nullptr);
}

IPL::Image::~Image()
{
	if (_pointer_array)
		delete _pointer_array;

	
}

int IPL::Image::Rows() const
{
	return _pointer_array->Rows();
}

int IPL::Image::Cols() const
{
	return _pointer_array->Cols();
}

IPL::Image& IPL::Image::operator=(const Image &img)
{
	if (_pointer_array)
	{
		delete _pointer_array;
	}

	
}

