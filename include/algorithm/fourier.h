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

        /** \brief  一维离散傅里叶变换
         *  \details X[m] = sum(n=0..N-1) data[n] * exp(-j*2*pi*m*n/M)，N 为 data 的长度
         *  \param[in] data 输入序列（实数或复数），长度记为 N
         *  \param[in] M    变换点数；M <= 0 时取 M = N，即对整段输入做 N 点 DFT
         *  \return 长度为 M 的复数频谱
         *  \note   复杂度 O(M*N)，需要 M 为 2 的幂时请改用 FFT
         */
        static std::vector<std::complex<double>> DFT(const std::vector<double>& data, int M = 0);
        static std::vector<std::complex<double>> DFT(const std::vector<std::complex<double>>& data, int M = 0);

        /** \brief  一维离散傅里叶逆变换
         *  \details x[n] = (1/M) * sum(m=0..M-1) freq_data[m] * exp(j*2*pi*m*n/M)，n = 0..N-1；
         *           M 为频谱长度即变换点数，归一化系数恒为 1/M，与 N 无关
         *  \param[in] freq_data 待逆变换的一维复数频谱，长度记为 M
         *  \param[in] N         期望输出的时域样本数；N <= 0 时取 N = M，
         *                       即完整还原 M 点逆变换的结果
         *  \return 长度为 N 的复数向量（时域），已含 1/M 归一化，理想情况下虚部为 0
         *  \note   正变换做过补零时（DFT(data, M)，M > data.size()），
         *          这里传 N = data.size() 即可截回原始长度的序列
         *  \note   N > M 时输出是 M 点逆变换结果的周期延拓（周期为 M）；
         *          N < M 时仅截取前 N 个样本，其余样本被丢弃
         *  \note   复杂度 O(M*N)；freq_data 为空时返回空向量
         */
        static std::vector<std::complex<double>> IDFT(const std::vector<std::complex<double>>& freq_data, int N = 0);

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
