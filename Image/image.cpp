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
	// �Ը�ֵ
	if (_Data == rhs._Data)
	{
		return *this;
	}

	// ���ͷ������ڴ�
	if (_Data)
	{
		free(_Data);
	}

	// ������ֵ
	_size = rhs._size;
	_Data = malloc(_size);
	memcpy(_Data, rhs._Data, _size);
	return *this;
}

IPL::_BaseArray& IPL::_BaseArray::operator=(_BaseArray &&rhs)
{
	// �Ը�ֵ
	if (_Data == rhs._Data)
	{
		return *this;
	}

	// ���ͷ������ڴ�
	if (_Data)
	{
		free(_Data);
	}

	// �ƶ���ֵ
	_size = rhs._size;
	_Data = rhs._Data;

	rhs._size = 0;
	rhs._Data = nullptr;
	return *this;
}
