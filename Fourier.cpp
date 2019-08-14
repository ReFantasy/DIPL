#include "Fourier.h"
#include <cassert>

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

const std::complex<double>& Eulerform::GetComplex() const
{
	return _com;
}




Fourier::Fourier()
{
}

Fourier::~Fourier()
{
}

std::vector<std::complex<double>> Fourier::DFT(const std::vector<double> &array_in) const
{
	int M = array_in.size();
	std::vector<std::complex<double>> array_out(M, std::complex<double>{});

	for (int i = 0; i < M; i++)
	{
		std::complex<double> tmp;
		for (int j = 0; j < M; j++)
		{
			Eulerform el(1, -2.0*PI*i*j / M);
			tmp += (array_in[j] * el.GetComplex());
		}
		array_out[i] = tmp;
	}

	return array_out;
}

std::vector<double> Fourier::IDFT(const std::vector<std::complex<double>> &array_in, std::vector<std::complex<double>> *pout_media)const
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


vector<vector<complex<double>>> Fourier::DFT(const vector<vector<double>> &array_in) const
{
	assert(array_in.size() > 0);
	assert(array_in[0].size() > 0);

	int M = array_in.size();
	int N = array_in[0].size();

	vector<vector<complex<double>>> array_out(M, vector<complex<double>>(N, 0));

	for (int u = 0; u < M; u++)
	{
		for (int v = 0; v < N; v++)
		{
			std::complex<double> tmp;

			for (int x = 0; x < M; x++)
			{
				for (int y = 0; y < N; y++)
				{
					Eulerform el(1, -2.0*PI*(u*x/M+v*y/N));
					tmp += (array_in[x][y] * el.GetComplex());
				}
			}

			array_out[u][v] = tmp;
		}
	}

	return array_out;
}

vector<vector<double>> Fourier::IDFT(const vector<vector<complex<double>>> &array_in, vector<vector<complex<double>>> *pout_media)const
{
	vector<vector<double>> array_out;






	return array_out;
}



