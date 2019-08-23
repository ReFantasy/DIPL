#ifndef __FOURIER_H__
#define __FOURIER_H__

#include <complex>
#include <vector>
#include <functional>
using std::vector;
using std::complex;

//#ifdef _DEBUG
#include <iostream>
//#endif

#define PI 3.141592653589793

namespace IPL
{
	class Fourier
	{

	public:
		Fourier();
		~Fourier();

		// 功能：一维离散傅里叶变换
		// 输入：一维向量
		// 输出：一维复数向量
		vector<complex<double>> DFT(const vector<double> &array_in)const;
		vector<complex<double>> DFT(const vector<complex<double>> &array_in)const;


		// 功能 ：一维离散傅里叶逆变换
		// 参数 ：需要进行逆变换的一维复数向量
		// 输出 ：一维浮点数据向量，即傅里叶逆变换的结果
		vector<complex<double>> IDFT(const vector<complex<double>> &array_in)const;


		// 功能：二维离散傅里叶变换
		// 输入：二维向量
		// 输出：二维复数向量
		vector<vector<complex<double>>> DFT(const vector<vector<double>> &array_in)const;
		vector<vector<complex<double>>> DFT(const vector<vector<complex<double>>> &array_in)const;


		// 功能 ：二维离散傅里叶逆变换
		// 参数 ：需要进行逆变换的二维复数向量
		// 输出 ：二维浮点数据向量，即傅里叶逆变换的结果
		vector<vector<complex<double>>> IDFT(const vector<vector<complex<double>>> &array_in)const;



		/** \brief One dimensional fast Fourier transform
		 *  \param[in] array_in one-dimensional complex vector
		 *  \return one-dimensional complex vector
		 */
		vector<complex<double>> FFT(const vector<complex<double>> &array_in)const;


		/** \brief Two dimensional fast Fourier transform
		 *  \param[in] array_in two-dimensional complex vector
		 *  \return two-dimensional complex vector
		 */
		vector<vector<complex<double>>> FFT(const vector<vector<complex<double>>> &array_in)const;


		/** \brief One dimensional fast Fourier transform
		 *  \param[in] array_in one-dimensional vector
		 *  \return one-dimensional complex vector
		 */
		vector<complex<double>> FFT(const vector<double> &array_in)const;


		/** \brief Two dimensional fast Fourier transform
		 *  \param[in] array_in two-dimensional complex vector
		 *  \return two-dimensional complex vector
		 */
		vector<vector<complex<double>>> FFT(const vector<vector<double>> &array_in)const;


		/** \brief One dimensional fast Fourier inversion transform
		 *  \param[in] array_in one-dimensional complex vector
		 *  \return one-dimensional complex vector
		 */
		vector<complex<double>> IFFT(const vector<complex<double>> &array_in)const;


		/** \brief Two dimensional fast Fourier inversion transform
		 *  \param[in] array_in two-dimensional complex vector
		 *  \return two-dimensional complex vector
		 */
		vector<vector<complex<double>>> IFFT(const vector<vector<complex<double>>> &array_in)const;

	};


	// 欧拉公式
	// thet 单位为弧度
	class Eulerform
	{
	public:
		Eulerform(const std::complex<double> &com);
		Eulerform(double mul, double thet);
		double Mul()const;
		double Thet()const;
		const std::complex<double>& GetComplex()const;

	private:
		std::complex<double> _com;
	};


	/** \brief check n = pow(2,k), k=1,2,3...
	 *  \param[in] n value to be checked
	 *  \return if n = pow(2,k),return true, or false
	 */
	bool Is2Power(int n);
	int Nearst2Power(int n);


}



#endif//__FOURIER_H__

