#ifndef __FOURIER_H__
#define __FOURIER_H__

#include <complex>
#include <vector>

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
        static std::vector<std::complex<double>> DFT(const std::vector<double>& array_double);
        static std::vector<std::complex<double>> DFT(const std::vector<std::complex<double>>& array_in);

        // 功能 ：一维离散傅里叶逆变换
        // 参数 ：需要进行逆变换的一维复数向量
        // 输出 ：一维浮点数据向量，即傅里叶逆变换的结果
        static std::vector<std::complex<double>> IDFT(const std::vector<std::complex<double>>& array_complex);

        // 功能：二维离散傅里叶变换
        // 输入：二维向量
        // 输出：二维复数向量
        static std::vector<std::vector<std::complex<double>>> DFT(const std::vector<std::vector<double>>& array_in);
        static std::vector<std::vector<std::complex<double>>>
        DFT(const std::vector<std::vector<std::complex<double>>>& array_in);

        // 功能 ：二维离散傅里叶逆变换
        // 参数 ：需要进行逆变换的二维复数向量
        // 输出 ：二维浮点数据向量，即傅里叶逆变换的结果
        static std::vector<std::vector<std::complex<double>>>
        IDFT(const std::vector<std::vector<std::complex<double>>>& array_in);

        /** \brief One dimensional fast Fourier transform
         *  \param[in] array_in one-dimensional complex vector
         *  \return one-dimensional complex vector
         */
        static std::vector<std::complex<double>> FFT(const std::vector<std::complex<double>>& array_in);

        /** \brief Two dimensional fast Fourier transform
         *  \param[in] array_in two-dimensional complex vector
         *  \return two-dimensional complex vector
         */
        static std::vector<std::vector<std::complex<double>>>
        FFT(const std::vector<std::vector<std::complex<double>>>& array_in);

        /** \brief One dimensional fast Fourier transform
         *  \param[in] array_in one-dimensional vector
         *  \return one-dimensional complex vector
         */
        static std::vector<std::complex<double>> FFT(const std::vector<double>& array_in);

        /** \brief Two dimensional fast Fourier transform
         *  \param[in] array_in two-dimensional complex vector
         *  \return two-dimensional complex vector
         */
        static std::vector<std::vector<std::complex<double>>> FFT(const std::vector<std::vector<double>>& array_in);

        /** \brief One dimensional fast Fourier inversion transform
         *  \param[in] array_in one-dimensional complex vector
         *  \return one-dimensional complex vector
         */
        static std::vector<std::complex<double>> IFFT(const std::vector<std::complex<double>>& array_in);

        /** \brief Two dimensional fast Fourier inversion transform
         *  \param[in] array_in two-dimensional complex vector
         *  \return two-dimensional complex vector
         */
        static std::vector<std::vector<std::complex<double>>>
        IFFT(const std::vector<std::vector<std::complex<double>>>& array_in);
    };

    // 欧拉公式 e^{jθ} = cosθ + jsinθ
    // 复数 C = |C|e^{jθ}=|C|(cosθ + jsinθ) θ单位为弧度
    class EulerTransform
    {
    public:
        EulerTransform(const std::complex<double>& com);
        EulerTransform(double theta);
        EulerTransform(double magnitude, double theta);
        double                      Magnitude() const;
        double                      Theta() const;
        const std::complex<double>& NativeComplex() const;

    private:
        std::complex<double> _complex;
    };

    /** \brief check n = pow(2,k), k=1,2,3...
     *  \param[in] n value to be checked
     *  \return if n = pow(2,k),return true, or false
     */
    bool Is2Power(int n);
    int  Nearst2Power(int n);

} // namespace IPL

#endif //__FOURIER_H__
