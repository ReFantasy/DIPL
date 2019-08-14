#ifndef __FOURIER_H__
#define __FOURIER_H__

#include <complex>
#include <vector>

#ifdef _DEBUG
#include <iostream>
#endif

#define PI 3.141592653589793

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

class Fourier
{
public:
	Fourier();
	~Fourier();

	// 功能：一维离散傅里叶变换
	// 输入：一维浮点数据向量
	// 输出：一维复数向量
	std::vector<std::complex<double>> DFT(const std::vector<double> &array_in)const;


	 // 功能 ：一维离散傅里叶逆变换
	 // 参数1：需要进行逆变换的一维复数向量
	 // 参数2：一维复数向量的指针，用于返回逆变换的中间计算结果,如果不需要可以传递空参数
	 // 输出 ：一维浮点数据向量，即傅里叶逆变换的结果
	std::vector<double> IDFT(const std::vector<std::complex<double>> &array_in,
		std::vector<std::complex<double>> *pout_media = nullptr);

};




//Fourier fourier;
//vector<double> input = { 1.5,2.3,4.7,4.1 };
//auto res = fourier.DFT(input);
//
//for (int i = 0; i < res.size(); i++)
//{
//	//cout << i << " : " << res[i].real() << "  " << res[i].imag() << endl;
//	printf("%d : %.4f  %.4f\n", i, res[i].real(), res[i].imag());
//}
//
//cout << "逆变换" << endl;
//std::vector<std::complex<double>> ires_midea;
//auto ires = fourier.IDFT(res, &ires_midea);
//for (int i = 0; i < ires.size(); i++)
//{
//	cout << ires[i] << endl;
//}
//
//cout << "逆变换中间过程数据" << endl;
//for (int i = 0; i < ires_midea.size(); i++)
//{
//	//cout << i << " : " << res[i].real() << "  " << res[i].imag() << endl;
//	printf("%d : %.4f  %.4f\n", i, ires_midea[i].real(), ires_midea[i].imag());
//}


#endif//__FOURIER_H__

