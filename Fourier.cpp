#include "Fourier.h"

Eulerform::Eulerform(const std::complex<double> &com)
	:_com(com)
{

}

Eulerform::Eulerform(double mul, double thet)
{
	double re = mul * cos(thet);
	double im = mul * sin(thet);
	_com = std::complex<double>(re, im);
}

double Eulerform::Mul() const
{
	return std::abs(_com);
}

double Eulerform::Thet() const
{
	return std::arg(_com);
}


Fourier::Fourier()
{
}


Fourier::~Fourier()
{
}

const std::complex<double>& Eulerform::GetComplex() const
{
	return _com;
}



std::vector<std::complex<double>> Fourier::fourier(const std::vector<double> &array_in) const
{
	int count = array_in.size();
	std::vector<std::complex<double>> array_out(count, std::complex<double>{});

	for (int i = 0; i < count; i++)
	{
		std::complex<double> tmp;
		for (int j = 0; j < count; j++)
		{
			Eulerform el(1, -2.0*PI*i*j / count);
			tmp += (array_in[j] * el.GetComplex());
		}
		array_out[i] = tmp;
	}

	return array_out;
}

std::vector<double> Fourier::InversionFourier(const std::vector<std::complex<double>> &array_in, std::vector<std::complex<double>> *pout_media)
{
	int M = array_in.size();
	std::vector<double> array_out(M, 0);
	std::vector<std::complex<double>> array_out_com(M, std::complex<double>{});

	for (int i = 0; i < M; i++)
	{
		std::complex<double> tmp;
		for (int j = 0; j < M; j++)
		{
			Eulerform el(1, 2.0*PI*i*j / M);
			tmp += (array_in[j] * el.GetComplex());
		}
		array_out_com[i] = { tmp.real() / M, tmp.imag() / M };
	}


	if (pout_media)
	{
		*pout_media = array_out_com;
	}

	for (int i = 0; i < M; i++)
	{
		array_out[i] = array_out_com[i].real();
	}

	return array_out;
}


