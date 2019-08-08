#ifndef __IMAGE_H__
#define __IMAGE_H__
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include "../io/io.h"

#define NAMESPACE_BEGIN namespace IPL{
#define NAMESPACE_END }

namespace IPL {

	/************************************************************************
	 *  基本数组类
	 *  以字节的形式保存连续一维数组数据
	 ************************************************************************/
	class _BaseArray
	{
	public:
		// 默认构造
		explicit _BaseArray(int size);

		// 拷贝构造
		_BaseArray(const _BaseArray &rhs);

		// 移动构造
		_BaseArray(_BaseArray &&rhs);

		// 拷贝赋值
		virtual _BaseArray& operator=(const _BaseArray &rhs);

		// 移动赋值
		virtual _BaseArray& operator=(_BaseArray &&rhs);

		virtual ~_BaseArray();

		virtual int Rows() const { return 1; };
		virtual int Cols()const { return _size; };
		void* Data()const { return _Data; }
		virtual void Print()const {}
		virtual _BaseArray* GetInstance();

	protected:
		void *_Data;
		int _size;

	};


	/************************************************************************
	 *  二维数组类
	 *  继承自一维基本数组类，提供二维数据的读写操作
	 ************************************************************************/
	template<typename T>
	class Array2D :public _BaseArray
	{
	public:
		using type = Array2D<T>;

		Array2D() = delete;

		// 构造函数
		Array2D(int rows, int cols, T t = T{})
			:_rows(rows), _cols(cols), _BaseArray(rows*cols * sizeof(T))
		{
			// 初始化数组数据
			T* tmp = (T*)(_Data);
			for (int i = 0; i < _rows*_cols; i++) {
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
		virtual Array2D& operator=(const Array2D &rhs)
		{
			_rows = rhs._rows;
			_cols = rhs._cols;
			_BaseArray::operator=(rhs);
			return *this;
		}

		// 移动赋值
		virtual Array2D& operator=(Array2D &&rhs)
		{
			_rows = rhs._rows;
			_cols = rhs._cols;
			_BaseArray::operator=(std::move(rhs));

			rhs._rows = 0;
			rhs._cols = 0;
			return *this;
		}

	public:
		virtual int Rows()const { return _rows; }
		virtual int Cols()const { return _cols; }
		virtual const T* operator[](int i)const
		{
			const T* tmp = (const T*)(_Data);
			return tmp + i * _cols;
		}

		virtual T* operator[](int i)
		{
			T* tmp = (T*)(_Data);
			return tmp + i * _cols;
		}

		virtual void Print()const
		{
			//std::cout << typeid(*this).name() << std::endl;
			for (int i = 0; i < _rows; i++)
			{
				for (int j = 0; j < _cols; j++)
				{
					std::cout << (*this)[i][j] << " ";
				}
				std::cout << std::endl;
			}
		}

		// 返回当前对象的拷贝
		_BaseArray* GetInstance()
		{
			_BaseArray *p = new Array2D(*this);
			return p;
		}
	protected:
		int _rows;
		int _cols;
	};

	enum ImgType {
		IMG_NONE, IMG_8UC1, IMG_32IC1, IMG_64FC1
	};



	/************************************************************************
	 *  图像类
	 *  继承自二维数组类
	 ************************************************************************/
	class Image
	{
	public:
		// 构造函数
		Image(int rows, int cols, ImgType img_type = ImgType::IMG_32IC1);

		// 拷贝构造
		Image(const Image &rhs);

		// 移动构造
		Image(Image &&rhs);

		// 拷贝赋值
		Image& operator=(const Image &rhs);

		// 移动赋值
		Image& operator=(Image &&rhs);

		template<typename _Ty = int>
		_Ty& SetValue(int row, int cols)
		{
			auto tmp = (char*)Data() + (row* _pArray2D->Cols() + cols) * sizeof(_Ty);
			return *(_Ty*)tmp;
		}

		template<typename _Ty = int>
		_Ty GetValue(int row, int cols)const
		{
			auto tmp = (char*)Data() + (row* _pArray2D->Cols() + cols) * sizeof(_Ty);
			return *(_Ty*)tmp;
		}

		// 析构函数
		virtual ~Image();



	public:
		void* Data()const;
		int Rows()const;
		int Cols()const;
		void Print()const;


	private:
		_BaseArray *_pArray2D = nullptr;
	};

	Image imread(std::string s, ImgType img_type = ImgType::IMG_32IC1);
	void Imshow(const std::string win_name, const Image &img, ImgType img_type = ImgType::IMG_32IC1);
	void WaitKey(int time);
	void WaitKey();
}
#endif//__IMAGE_H__