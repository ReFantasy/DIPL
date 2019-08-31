#include "Fourier.h"
#include <cassert>
namespace IPL
{



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
			/*tmp[i]._Val[0] = array_in[i];
			tmp[i]._Val[1] = 0;*/
			tmp[i] = { array_in[i], 0 };
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

	vector<complex<double>> Fourier::FFT(const vector<complex<double>> &in)const
	{
		assert(Is2Power(in.size()));

		std::vector<std::complex<double>> out(in.size(), std::complex<double>{0, 0});

		int K = in.size() / 2;
		if (K > 1)
		{
			std::vector<std::complex<double>> even(K, std::complex<double>{0, 0});
			std::vector<std::complex<double>> odd(K, std::complex<double>{0, 0});
			for (int i = 0; i < in.size(); i += 2)
			{
				even[i / 2] = in[i];
				odd[i / 2] = in[i + 1];
			}

			auto even_fourier = std::move(FFT(even));
			auto odd_fourier = std::move(FFT(odd));



			std::vector<std::complex<double>> W_2k_u(K, std::complex<double>{0, 0});
			for (int i = 0; i < K; i++)
			{
				IPL::Eulerform e(1, -2.0*PI*i / 2 / K);
				W_2k_u[i] = odd_fourier[i] * e.GetComplex();
			}

			for (int i = 0; i < K; i++)
			{
				out[i] = even_fourier[i] + W_2k_u[i];
			}
			for (int i = 0; i < K; i++)
			{
				out[i + K] = even_fourier[i] - W_2k_u[i];
			}
		}
		else
		{
			assert(K == 1);
			std::complex<double> even0 = in[0];
			std::complex<double> odd0 = in[1];
			out[0] = even0 + odd0;
			out[1] = even0 - odd0;
		}

		return out;
	}

	vector<complex<double>> Fourier::FFT(const vector<double> &array_in) const
	{
		vector<complex<double>> in_complex(array_in.size(), { 0,0 });
		for (int i = 0; i < array_in.size(); i++)
		{
			/*in_complex[i]._Val[0] = array_in[i];
			in_complex[i]._Val[1] = 0;*/
			in_complex[i] = { array_in[i] ,0 };
		}

		return FFT(in_complex);
	}

	vector<vector<complex<double>>> Fourier::FFT(const vector<vector<complex<double>>> &array_in) const
	{
		assert(array_in.size() > 0);
		assert(array_in[0].size() > 0);

		int M = array_in.size();
		int N = array_in[0].size();

		vector<vector<complex<double>>> array_out;

		// 先进行行变换
		for (int i = 0; i < M; i++)
		{
			array_out.push_back(std::move(FFT(array_in[i])));
		}

		// 再进行列变换
		vector<complex<double>> tmp(M, { 0,0 });
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				tmp[k] = array_out[k][j];
			}
			auto dft_col = std::move(FFT(tmp));

			for (int k = 0; k < M; k++)
			{
				array_out[k][j] = dft_col[k];
			}
		}
		return array_out;
	}

	vector<vector<complex<double>>> Fourier::FFT(const vector<vector<double>> &array_in) const
	{
		assert(array_in.size() > 0);
		assert(array_in[0].size() > 0);
		int rows = array_in.size();
		int cols = array_in[0].size();

		vector<vector<complex<double>>> tmp(rows, vector<complex<double>>(cols, complex<double>{0, 0}));
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				/*tmp[i][j]._Val[0] = array_in[i][j];
				tmp[i][j]._Val[1] = 0;*/
				tmp[i][j] = { array_in[i][j], 0 };
			}
		}

		return FFT(tmp);

	}

	/*
	 *  We use FFT to compute IFFT.
	 *  To get f(x,y), we just need to input F*(u,v), which is the complex conjugate of the F(u,v), to FFT,
	 *  and the return of FFT is the value MNf*(x,y). Once we can know MNf*(x,y), we can get f(x,y) easily.
	 */
	vector<complex<double>> Fourier::IFFT(const vector<complex<double>> &array_in) const
	{
		int cnt = array_in.size();

		vector<complex<double>> array_in_conjugate(cnt, complex<double>{});
		for (int i = 0; i < cnt; i++)
		{
			/*array_in_conjugate[i]._Val[0] = array_in[i]._Val[0];
			array_in_conjugate[i]._Val[1] = -array_in[i]._Val[1];*/
			array_in_conjugate[i] = conj(array_in[i]);
		}

		auto MN_f_conjugate = FFT(array_in_conjugate);

		vector<complex<double>> f_conjugate(cnt, { 0,0 });
		for (int i = 0; i < cnt; i++)
		{
			f_conjugate[i] = complex<double>{ MN_f_conjugate[i].real() / cnt,MN_f_conjugate[i].imag() / cnt };
		}

		vector<complex<double>> f(cnt, { 0,0 });
		for (int i = 0; i < cnt; i++)
		{
			f[i] = complex<double>{ f_conjugate[i].real(),-f_conjugate[i].imag() };
			
		}

		return f;
	}

	vector<vector<complex<double>>> Fourier::IFFT(const vector<vector<complex<double>>> &array_in) const
	{
		assert(array_in.size() > 0);
		assert(array_in[0].size() > 0);

		int M = array_in.size();
		int N = array_in[0].size();

		vector<vector<complex<double>>> array_out;

		// 先进行行变换
		for (int i = 0; i < M; i++)
		{
			array_out.push_back(std::move(IFFT(array_in[i])));
		}

		// 再进行列变换
		vector<complex<double>> tmp(M, { 0,0 });
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				tmp[k] = array_out[k][j];
			}
			auto dft_col = std::move(IFFT(tmp));

			for (int k = 0; k < M; k++)
			{
				array_out[k][j] = dft_col[k];
			}
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
		std::vector<std::vector<std::complex<double>>> tmp(array_in.size(), std::vector<std::complex<double>>(array_in[0].size(), { 0,0 }));
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				/*tmp[i][j]._Val[0] = array_in[i][j];
				tmp[i][j]._Val[1] = 0;*/
				tmp[i][j] = { array_in[i][j], 0 };
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
		vector<complex<double>> tmp(M, { 0,0 });
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

	bool Is2Power(int n)
	{
		if (n <= 1)
			return false;

		int max_bits = sizeof(int) * 8;

		int bit = 0x1;
		for (int i = 0; i < max_bits; i++)
		{
			if (!(bit ^n))
			{
				return true;
			}
			else
			{
				bit <<= 1;
			}
		}

		return false;
	}

	int Nearst2Power(int n)
	{
		int max_bits = sizeof(int) * 8;
		vector<int> table(max_bits, 0);

		int bit = 0x1;
		for (int i = 0; i < max_bits; i++)
		{
			table[i] = bit;
			bit <<= 1;
		}

		


		vector<int> distance(max_bits, 0);
		for (int i = 0; i < max_bits; i++)
		{
			distance[i] = abs(table[i] - n);
		}

		int index = 0;
		int minv = distance[0];
		for (int i = 1; i < max_bits; i++)
		{
			if (minv > distance[i])
			{
				minv = distance[i];
				index = i;
			}
		}

		return table[index];

	}

}
