#ifndef __IMAGE_H__
#define __IMAGE_H__
#include <iostream>
#include <cassert>

#define NAMESPACE_BEGIN namespace IPL{
#define NAMESPACE_END }

NAMESPACE_BEGIN

// 二维矩阵类
template<typename T>
class Array2D
{
public:
	Array2D() :_Data(nullptr) {}
	Array2D(int rows, int cols, T pixel_value = T{})
		:_rows(rows), _cols(cols),_Data(nullptr)
	{
		assert((rows > 0) && (cols > 0));
		_Data = new T[_rows*_cols]{};
		
	}
	
	// 拷贝构造
	Array2D(const Array2D&rhs)
	{
		_rows = rhs._rows;
		_cols = rhs._cols;
		_Data = new T[_rows*_cols]{};
		memcpy(_Data, rhs._Data, sizeof(T)*_rows*_cols);

	}
	
	// 移动构造
	Array2D(Array2D &&rhs)
	{
		_rows = rhs._rows;
		_cols = rhs._cols;
		_Data = rhs._Data;

		rhs._rows = 0;
		rhs._cols = 0;
		rhs._Data = nullptr;
	}

	// 拷贝赋值
	virtual Array2D& operator=(const Array2D&rhs)
	{
		// 自赋值
		if (_Data == rhs._Data)
			return *this;

		if (_Data)
		{
			delete[] _Data;
		}

		_rows = rhs._rows;
		_cols = rhs._cols;
		_Data = new T[_rows*_cols]{};
		memcpy(_Data, rhs._Data, sizeof(T)*_rows*_cols);

		return *this;
	}

	// 移动赋值

	virtual Array2D& operator=(Array2D &&rhs)
	{
		// 自赋值
		if (_Data == rhs._Data)
			return *this;

		if (_Data)
		{
			delete[] _Data;
		}

		_rows = rhs._rows;
		_cols = rhs._cols;
		_Data = rhs._Data;

		rhs._rows = 0;
		rhs._cols = 0;
		rhs._Data = nullptr;

		return *this;
	}

	// 析构
	virtual ~Array2D()
	{
		if (_Data)
			delete[] _Data;
	}

public:
	virtual T Pixel(int row, int col)const
	{
		return _Data[row*_cols + col];
	}

	// 重载运算符
	virtual T* operator[](size_t i)
	{
		return &_Data[i*_cols];
	}
	virtual const T* operator[](size_t i)const
	{
		return &_Data[i*_cols];
	}


	virtual void Print()const
	{
		std::cout << "Array2D address:" << _Data << std::endl;
		for (int i = 0; i < _rows; i++)
		{
			for (int j = 0; j < _cols; j++)
			{
				std::cout << Pixel(i, j) << " ";
			}
			std::cout << std::endl;
		}
	}

private:
	T *_Data;
	int _rows;
	int _cols;
};

template<typename T>
class Image:public Array2D<T>
{
public:
	Image() :Array2D() {}
	Image(int rows, int cols, T pixel_value = T{}) :Array2D<T>(rows, cols) {  }
	Image(const Image&rhs) :Array2D<T>(rhs) {}
	Image(Image &&rhs) :Array2D<T>(std::move(rhs)) {}

	Image& operator=(const Image&rhs) 
	{
		Array2D<T>::operator =(rhs);
		return *this;
	}
	Image& operator=(Image &&rhs)
	{
		Array2D<T>::operator =(std::move(rhs));
		return *this;
	}
	

};

NAMESPACE_END
#endif//__IMAGE_H__