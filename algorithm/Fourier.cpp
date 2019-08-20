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
	/*int M = array_in.size();
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

	return array_out;*/

	std::vector<std::complex<double>> tmp(array_in.size(), { 0,0 });
	for (int i = 0; i < array_in.size(); i++)
	{
		tmp[i]._Val[0] = array_in[i];
		tmp[i]._Val[1] = 0;
	}

	return DFT(tmp);
}

vector<complex<double>> Fourier::DFT(const vector<complex<double>> &array_in) const
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

vector<complex<double>> Fourier::IDFT(const std::vector<std::complex<double>> &array_in)const
{
	int M = array_in.size();
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

	return array_out_com;
}


vector<vector<complex<double>>> Fourier::DFT(const vector<vector<double>> &array_in) const
{
	assert(array_in.size() > 0);
	assert(array_in[0].size() > 0);

	int M = array_in.size();
	int N = array_in[0].size();
	std::vector<std::vector<std::complex<double>>> tmp(array_in.size(), std::vector<std::complex<double>>(array_in[0].size(), {0,0}));
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tmp[i][j]._Val[0] = array_in[i][j];
			tmp[i][j]._Val[1] = 0;
		}
	}

	return DFT(tmp);
}
vector<vector<complex<double>>> Fourier::DFT(const vector<vector<complex<double>>> &array_in) const
{


	/*    严格按照傅里叶变换公式计算
	 *
	 * assert(array_in.size() > 0);
	 * assert(array_in[0].size() > 0);
	 * 
	 * int M = array_in.size();
	 * int N = array_in[0].size();
	 * 
	 * vector<vector<complex<double>>> array_out(M, vector<complex<double>>(N, 0));
     * 
	 * for (int u = 0; u < M; u++)
	 * {
	 *	 for (int v = 0; v < N; v++)
	 *	 {
	 *		 std::complex<double> tmp(0, 0);
     *
	 *		 for (int x = 0; x < M; x++)
	 *		 {
	 *	 		 for (int y = 0; y < N; y++)
	 *			 {
	 *				 Eulerform el(1, -2.0*PI*(u*x / (double)M + v * y / (double)N));
	 *				 tmp += (array_in[x][y] * el.GetComplex());
	 *			 }
	 *		 }
	 *		 array_out[u][v] = tmp;
	 *	 }
	 * }
     *
	 * return array_out;
	 */


	/*
	 *
	 *  离散傅里叶变换的优化版本 公式：数字图像处理第三版 P187
	 *
	 */
	std::cout << "----------------------------" << std::endl;
	assert(array_in.size() > 0);
	assert(array_in[0].size() > 0);

	int M = array_in.size();
	int N = array_in[0].size();

	vector<vector<complex<double>>> array_out;

	// 先进行行变换
	for (int i = 0; i < M; i++)
	{
		array_out.push_back(std::move(DFT(array_in[i])));
	}

	// 再进行列变换
	vector<complex<double>> tmp(M, {0,0});
	for (int j = 0; j < N; j++)
	{
		for (int k = 0; k < M; k++)
		{
			tmp[k] = array_out[k][j];
		}
		auto dft_col = std::move(DFT(tmp));

		for (int k = 0; k < M; k++)
		{
			array_out[k][j] = dft_col[k];
		}
	}
	return array_out;
}



vector<vector<complex<double>>> Fourier::IDFT(const vector<vector<complex<double>>> &array_in)const
{

	// 原始版本
	/*assert(array_in.size() > 0);
	assert(array_in[0].size() > 0);

	int M = array_in.size();
	int N = array_in[0].size();


	vector<vector<complex<double>>> array_out_com(M, vector<complex<double>>(N, complex<double>()));

	for (int x = 0; x < M; x++)
	{
		for (int y = 0; y < N; y++)
		{
			complex<double> tmp;

			for (int u = 0; u < M; u++)
			{
				for (int v = 0; v < N; v++)
				{
					Eulerform el(1, 2.0*PI*(u*x / (double)M + v * y / (double)N));
					tmp += (array_in[u][v] * el.GetComplex());
				}
			}

			array_out_com[x][y] = { tmp.real() / M / N, tmp.imag() / M / N };

		}
	}

	return array_out_com;*/
	
	/*
	 *
	 *  离散傅里叶逆变换的优化版本 公式：数字图像处理第三版 P187
	 *
	 */
	std::cout << "----------------------------" << std::endl;
	assert(array_in.size() > 0);
	assert(array_in[0].size() > 0);

	int M = array_in.size();
	int N = array_in[0].size();

	vector<vector<complex<double>>> array_out;

	// 先进行行变换
	for (int i = 0; i < M; i++)
	{
		array_out.push_back(std::move(IDFT(array_in[i])));
	}

	// 再进行列变换
	vector<complex<double>> tmp(M, { 0,0 });
	for (int j = 0; j < N; j++)
	{
		for (int k = 0; k < M; k++)
		{
			tmp[k] = array_out[k][j];
		}
		auto dft_col = std::move(IDFT(tmp));

		for (int k = 0; k < M; k++)
		{
			array_out[k][j] = dft_col[k];
		}
	}
	return array_out;

}


