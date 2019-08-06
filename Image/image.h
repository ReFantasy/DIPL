#ifndef __IMAGE_H__
#define __IMAGE_H__
#include <iostream>
#include <cassert>
#include <vector>
#include "../io/io.h"

#define NAMESPACE_BEGIN namespace IPL{
#define NAMESPACE_END }

NAMESPACE_BEGIN

class _BaseArray 
{
public:
	// 默认构造
	explicit _BaseArray() { _Data = nullptr; _size = 0; };
	explicit _BaseArray(int size);

	// 拷贝构造
	_BaseArray(const _BaseArray &rhs);

	// 移动构造
	_BaseArray(_BaseArray &&rhs);

	// 拷贝赋值
	virtual _BaseArray& operator=(const _BaseArray &rhs);

	// 移动赋值
	virtual _BaseArray& operator=( _BaseArray &&rhs);

	virtual ~_BaseArray();

//protected:
	void *_Data;
	int _size;

};

template<typename T>
class Array2D :public _BaseArray
{
public:
	Array2D() = delete;
	// 构造函数
	Array2D(int rows, int cols, T t = T{})
		:_rows(rows),_cols(cols), _BaseArray(rows*cols * sizeof(T))
	{
//#ifdef _DEBUG
//		std::cout << "Array2D data: " << _BaseArray::_Data << std::endl;
//#endif

		// 初始化数组数据
		T* tmp = (T*)(_Data);
		for (int i = 0; i < _rows*_cols; i++){
			tmp[i] = t;
		}



	}

	// 拷贝构造
	Array2D(const Array2D &rhs)
		:_BaseArray(rhs)
	{
		_rows = rhs._rows;
		_cols = rhs._cols;
		
	}

	// 移动构造
	Array2D(Array2D &&rhs)
		:_BaseArray(std::move(rhs))
	{
		_rows = rhs._rows;
		_cols = rhs._cols;

		rhs._rows = 0;
		rhs._cols = 0;
		
	}

	// 拷贝赋值
	Array2D& operator=(const Array2D &rhs)
	{
		_rows = rhs._rows;
		_cols = rhs._cols;
		_BaseArray::operator=(rhs);
		return *this;
	}

	// 移动赋值
	Array2D& operator=(Array2D &&rhs)
	{
		_rows = rhs._rows;
		_cols = rhs._cols;
		_BaseArray::operator=(std::move(rhs));

		rhs._rows = 0;
		rhs._cols = 0;
		return *this;
	}

public:
	int Rows()const { return _rows; }
	int Cols()const { return _cols; }
	const T* operator[](int i)const
	{
		const T* tmp = (const T*)(_Data);
		return tmp + i * _cols;
	}

	T* operator[](int i)
	{
		T* tmp = (T*)(_Data);
		return tmp + i * _cols;
	}

	void Print()const
	{
		std::cout << typeid(*this).name() << std::endl;
		for (int i = 0; i < _rows; i++)
		{
			for (int j = 0; j < _cols; j++)
			{
				std::cout << (*this)[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
private:


protected:
	int _rows;
	int _cols;
};



NAMESPACE_END
#endif//__IMAGE_H__