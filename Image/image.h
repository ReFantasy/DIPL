#ifndef __IMAGE_H__
#define __IMAGE_H__
#include <iostream>
#include <cassert>
#include <vector>
#include "../io/io.h"

#define NAMESPACE_BEGIN namespace IPL{
#define NAMESPACE_END }

NAMESPACE_BEGIN

class _BaseArray2D {
public:
	_BaseArray2D() {}
	_BaseArray2D(int rows, int cols) :_rows(rows), _cols(cols) {}

	virtual int Rows()const
	{
		return _rows;
	}

	virtual int Cols()const
	{
		return _cols;
	}
	virtual int SetRows(int rows)
	{
		_rows = rows;
	}

	virtual int SetCols(int cols)
	{
		_cols = cols;
	}

	void* Data()
	{
		return _Data;
	}
	virtual int SetData(void* data)
	{
		_Data = data;
	}

	virtual ~_BaseArray2D() {}

protected:
	int _rows = 0;
	int _cols = 0;
	void *_Data = nullptr;

};

// ��ά������
template<typename T = double>
class Array2D:public _BaseArray2D
{
public:


	Array2D(std::vector<std::vector<T>> vec, T pixel_value = T{})
	{
		assert(vec.size() > 0 && vec[0].size() > 0);
		_rows = vec.size();
		_cols = vec[0].size();

		_Data = new T[_rows*_cols]{ };
		for (int i = 0; i < _rows*_cols; i++)
		{
			_Data[i] = pixel_value;
		}
	}
	
	Array2D(int rows, int cols, T pixel_value = T{})
		:_BaseArray2D(rows,cols)
	{
		assert((rows > 0) && (cols > 0));
		_Data = new T[_rows*_cols]{ };
		for (int i = 0; i < rows*cols; i++)
		{
			((T*)_Data)[i] = pixel_value;
		}
	}
	
	// ��������
	Array2D(const Array2D&rhs)
	{
		_rows = rhs._rows;
		_cols = rhs._cols;
		_Data = new T[_rows*_cols]{};
		memcpy(_Data, rhs._Data, sizeof(T)*_rows*_cols);

	}
	
	// �ƶ�����
	Array2D(Array2D &&rhs)
	{
		_rows = rhs._rows;
		_cols = rhs._cols;
		_Data = rhs._Data;

		rhs._rows = 0;
		rhs._cols = 0;
		rhs._Data = nullptr;
	}

	// ������ֵ
	virtual Array2D& operator=(const Array2D&rhs)
	{
		// �Ը�ֵ
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

	// �ƶ���ֵ

	virtual Array2D& operator=(Array2D &&rhs)
	{
		// �Ը�ֵ
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

	// ����
	virtual ~Array2D()
	{
		auto p = ((T*)_Data);
		if (p)
			delete[] p;
	}

public:
	virtual T Pixel(int row, int col)const
	{
		return ((T*)_Data)[row*_cols + col];
	}

	// ���������
	virtual T* operator[](size_t i)
	{
		return &((T*)_Data)[i*_cols];
	}
	virtual const T* operator[](size_t i)const
	{
		return (T*)(&((T*)_Data)[i*_cols]);
	}


	virtual void Print()const
	{
		std::cout << "Data address: " << _Data << std::endl;
		for (int i = 0; i < _rows; i++)
		{
			for (int j = 0; j < _cols; j++)
			{
				std::cout << Pixel(i, j) << " ";
			}
			std::cout << std::endl;
		}
	}

	
	
};

template<typename T>
class Iterator
{
public:
	Iterator(T*p):_p(p) {}

	T* operator++() // ǰ������ֻ��һ������
	{
		_p += 1;
		return _p;
	}

	T* operator++(int) // ������������������һ��int����
	{
		T* tmp = _p;
		_p += 1;
		return tmp;
	}

	bool operator==(const Iterator& it)
	{
		return (_p == it._p);
	}
	bool operator!=(const Iterator& it)
	{
		return !(_p == it._p);
	}
	T& operator*()
	{
		return *_p;
	}
	const T& operator*()const
	{
		return *_p;
	}

private:
	T *_p;
};


enum PixType {
	NONE, IPL_8UC1, IPL_64FC1
};


class Image
{

public:
	// Ĭ�Ϲ���
	Image() = default;
	Image(int rows, int cols, PixType pix_type);

	// ��������
	Image(const Image &img);

	// �ƶ�����
	Image(Image &&img);

	// ������ֵ
	Image& operator=(const Image &img);

	// �ƶ���ֵ
	Image& operator=(Image &&img);

	int Rows()const;
	int Cols()const;

	void* Data()const
	{
		return _pointer_array->Data();
	}

	virtual ~Image();
	

private:
	
private:
	PixType _pix_type = NONE;
	_BaseArray2D *_pointer_array = nullptr;
	size_t _pix_type_size = 1;


};

NAMESPACE_END
#endif//__IMAGE_H__