#include "image.h"

IPL::_BaseArray::_BaseArray(int size)
{
	_size = size;
	_Data = malloc(_size);
//#ifdef _DEBUG
//	std::cout << "_BaseArray data: " << (void*)_Data << std::endl;
//#endif
}

IPL::_BaseArray::_BaseArray(const _BaseArray &rhs)
{
	_size = rhs._size;
	_Data = malloc(_size);
	memcpy(_Data, rhs._Data, _size);
}

IPL::_BaseArray::_BaseArray(_BaseArray &&rhs)
{
	_size = rhs._size;
	_Data = rhs._Data;

	rhs._size = 0;
	rhs._Data = nullptr;
}

IPL::_BaseArray::~_BaseArray()
{
	if (_Data)
	{
		free(_Data);
		_Data = nullptr;
	}
}

IPL::_BaseArray& IPL::_BaseArray::operator=(const _BaseArray &rhs)
{
	// 自赋值
	if (_Data == rhs._Data)
	{
		return *this;
	}

	// 先释放已有内存
	if (_Data)
	{
		free(_Data);
	}

	// 拷贝赋值
	_size = rhs._size;
	_Data = malloc(_size);
	memcpy(_Data, rhs._Data, _size);
	return *this;
}

IPL::_BaseArray& IPL::_BaseArray::operator=(_BaseArray &&rhs)
{
	// 自赋值
	if (_Data == rhs._Data)
	{
		return *this;
	}

	// 先释放已有内存
	if (_Data)
	{
		free(_Data);
	}

	// 移动赋值
	_size = rhs._size;
	_Data = rhs._Data;

	rhs._size = 0;
	rhs._Data = nullptr;
	return *this;
}

IPL::_BaseArray* IPL::_BaseArray::GetInstance()
{
	return new _BaseArray(_size);
}

IPL::Image::Image(int rows, int cols, ImgType img_type)
{
	switch (img_type)
	{
	case IPL::IMG_NONE:
		break;

	case IPL::IMG_8UC1:
		_pArray2D = new Array2D<unsigned char>(rows, cols, 'o');
		break;

	case IPL::IMG_32IC1:
		_pArray2D = new Array2D<int>(rows, cols, 0);
		break;

	case IPL::IMG_64FC1:
		break;

	default:
		break;
	}
}

IPL::Image::Image(const Image &rhs)
{
	_pArray2D = rhs._pArray2D->GetInstance();
}

IPL::Image::Image(Image &&rhs)
{
	_pArray2D = rhs._pArray2D;
	rhs._pArray2D = nullptr;
}

void* IPL::Image::Data() const
{
	return _pArray2D->Data();
}

int IPL::Image::Rows() const
{
	return _pArray2D->Rows();
}

int IPL::Image::Cols() const
{
	return _pArray2D->Cols();
}

IPL::Image::~Image()
{
	if (_pArray2D)
	{
		delete _pArray2D;
		_pArray2D = nullptr;
	}
}

void IPL::Image::Print() const
{
	if(_pArray2D)
	    _pArray2D->Print();
	else
	{
		std::cout << "image empty" << std::endl;
	}
}

IPL::Image& IPL::Image::operator=(const Image &rhs)
{
	if (this == &rhs)
		return *this;

	if (_pArray2D)
	{
		delete _pArray2D;
		_pArray2D = nullptr;
	}

	_pArray2D = rhs._pArray2D->GetInstance();

	return *this;
}

IPL::Image& IPL::Image::operator=(Image &&rhs)
{
	if (this == &rhs)
		return *this;

	if (_pArray2D)
	{
		delete _pArray2D;
		_pArray2D = nullptr;
	}

	_pArray2D = rhs._pArray2D;
	rhs._pArray2D = nullptr;

	return *this;
}

IPL::Image IPL::imread(std::string s, ImgType img_type)
{
	cv::Mat src;
	Image *pimg = nullptr;

	switch (img_type)
	{
	case IPL::IMG_NONE:
		break;
	case IPL::IMG_8UC1:
		//break;
	case IPL::IMG_32IC1:
		src = cv::imread(s, 0);
		//cv::imshow("IPL::imread", src);
		pimg = new Image(src.rows, src.cols, IMG_32IC1);
		for (int i = 0; i < src.rows; i++)
		{
			for (int j = 0; j < src.cols; j++)
			{
				pimg->SetValue<int>(i, j) = (int)src.data[i*src.cols + j];
			}
		}
		return *pimg;
		break;
	case IPL::IMG_64FC1:
		break;
	default:
		break;
	}

	return *pimg;
}

void IPL::Imshow(const std::string win_name, const Image &img, ImgType img_type)
{
	cv::Mat cvimg;
	switch (img_type)
	{
	case IPL::IMG_NONE:
		break;

	case IPL::IMG_8UC1:
		//break;
	case IPL::IMG_32IC1:
		cvimg.create(img.Rows(), img.Cols(), CV_8UC1);
		for (int i = 0; i < cvimg.rows; i++)
		{
			for (int j = 0; j < cvimg.cols; j++)
			{
				cvimg.data[i*cvimg.cols + j] = img.GetValue<int>(i, j);
			}
		}
		cv::imshow(win_name, cvimg);
		break;


	case IPL::IMG_64FC1:
		break;
	default:
		break;
	}
}

void IPL::WaitKey(int time)
{
	cv::waitKey(time);
}

void IPL::WaitKey()
{
	cv::waitKey();
}

