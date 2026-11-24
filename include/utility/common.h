#pragma once
#include "opencv2/opencv.hpp"
#include <complex>
#include <type_traits>
#include <vector>

namespace IPL
{

    int                              GetTerminalWidth(int fallback = 80);
    void                             PrintMatInfo(cv::Mat mat);
    std::vector<std::vector<double>> FreqOffset(const std::vector<std::vector<double>>& data);

    /************************************************************************
     *     实数数组与复数数组之间的转换
     ************************************************************************/
    std::vector<std::complex<double>>              Real2Complex(const std::vector<double>& vec);
    std::vector<std::vector<std::complex<double>>> Real2Complex(const std::vector<std::vector<double>>& vec);

    /** \brief 从复数中提取哪个分量转成实数
     */
    enum class ComplexComponent
    {
        Real,             // 实部 z.real()
        Imag,             // 虚部 z.imag()
        Magnitude,        // 幅值 |z|
        SquaredMagnitude, // 功率 |z|^2（std::norm）
        Phase,            // 相位 arg(z)，范围 (-pi, pi]
        LogMagnitude,     // 对数幅值 log(1 + |z|)，频谱显示的常用压缩
    };

    /** \brief 复数向量 -> 实数向量，按 comp 指定的分量转换
     *  \param[in] src  输入复数向量
     *  \param[in] comp 要提取的分量，默认取幅值
     *  \return 与 src 等长的实数向量
     */
    std::vector<double> Complex2Real(const std::vector<std::complex<double>>& src,
                                     ComplexComponent                         comp = ComplexComponent::Magnitude);

    /** \brief 二维复数向量 -> 二维实数向量，按 comp 指定的分量转换
     *  \param[in] src  输入二维复数向量（允许各行列数不同）
     *  \param[in] comp 要提取的分量，默认取幅值
     *  \return 与 src 同行数、逐行等长的二维实数向量
     */
    std::vector<std::vector<double>> Complex2Real(const std::vector<std::vector<std::complex<double>>>& src,
                                                  ComplexComponent comp = ComplexComponent::Magnitude);

    /** \brief 逐元素映射：把 std::vector<T> 转换成 std::vector<U>
     *  \details op 需可调用且接受 const T&；其返回值（去 cv/引用后）决定输出元素类型，
     *           例如 [](const std::complex<double>& z) { return std::abs(z) * 255.0; }
     */
    template<class T, class UnaryOp>
    [[nodiscard]] auto MapVector(const std::vector<T>& src, UnaryOp&& op)
        -> std::vector<std::remove_cvref_t<std::invoke_result_t<UnaryOp&, const T&>>>
    {
        using U = std::remove_cvref_t<std::invoke_result_t<UnaryOp&, const T&>>;
        std::vector<U> dst;
        dst.reserve(src.size());
        for (const auto& z : src)
            dst.push_back(op(z));
        return dst;
    }

    template<class T, class F>
    [[nodiscard]] auto MapVector(const std::vector<std::vector<T>>& src, F&& op)
        -> std::vector<std::vector<std::remove_cvref_t<std::invoke_result_t<F&, const T&>>>>
    {
        using U = std::remove_cvref_t<std::invoke_result_t<F&, const T&>>;
        std::vector<std::vector<U>> dst;
        dst.reserve(src.size());
        for (const auto& row : src)
        {
            std::vector<U> mapped;
            mapped.reserve(row.size()); // 不再走 1D 重载，行为与 1D 完全一致
            for (const auto& z : row)
                mapped.push_back(std::invoke(op, z));
            dst.push_back(std::move(mapped));
        }
        return dst;
    }

    /************************************************************************
     *     Mat 与二维数组之间的转换
     ************************************************************************/

    /** \brief  灰度化并把 cv::Mat 转为二维 double 向量
     *  \details 自动处理通道数：1 通道直接使用，3/4 通道按 BGR/BGRA 转灰度（丢弃 alpha）；
     *           深度统一转为 CV_64F（彩色 CV_64F 图像先降到 CV_32F 再灰度化，
     *           因为 cvtColor 只支持 8U/16U/32F）。
     *           不做缩放与归一化，返回的数值与原图像素值一致。
     *  \param[in] mat 输入图像，可为 8U/16U/32F/64F 的 1、3、4 通道图像
     *  \return 行优先的二维向量，尺寸为 mat.rows × mat.cols；
     *          mat 为空时返回空向量
     *  \note   通道数不是 1/3/4 时抛出 cv::Exception（StsBadArg）
     *  \note   每次调用按行分配内存，行数很大时（如上万行）开销可见；
     *          若只需一次遍历处理，建议直接使用 cv::Mat
     *  \sa     Vector2DToMat, MatToPreCenteredVector2D
     */
    std::vector<std::vector<double>> MatToVector2D(const cv::Mat& mat);

    /** \brief  二维 double 向量转为 CV_64FC1 的 Mat（精确，不缩放不裁剪）
     *  \details 用于需要保留 double 精度的中间结果，例如频谱、小波系数、
     *           或 cv::filter2D 等只接受浮点输入的接口；
     *           MatToVector2D 与本函数互为逆操作（无损往返）。
     *  \param[in] src 输入二维向量，各行长度必须相同
     *  \return CV_64FC1 单通道矩阵；src 为空时返回空 Mat
     *  \note   各行列数不一致时 CV_Assert 失败（Debug 与 Release 均生效）
     *  \note   若结果要用于 imshow/imwrite/直方图，请改用 Vector2DToMatU8；
     *          直接显示 CV_64F 会被 OpenCV 拒绝（Unsupported image depth）
     *  \sa     Vector2DToMatU8, MatToVector2D
     */
    cv::Mat Vector2DToMat(const std::vector<std::vector<double>>& src);

    /** \brief  灰度化并做棋盘调制 g(x,y) = f(x,y) * (-1)^(x+y)，为 DFT 中心化做准备
     *  \details 在空域乘 (-1)^(x+y) 后，DFT 的零频分量（DC）会落在频谱中心，
     *           等价于频域的 fftshift，但省去一次频谱重排；
     *           这是 Gonzalez《数字图像处理》中的标准做法。
     *           通道数与深度处理同 MatToVector2D。
     *  \param[in] mat 输入图像，可为 8U/16U/32F/64F 的 1、3、4 通道图像
     *  \return 已调制的二维 double 向量，尺寸为 mat.rows × mat.cols；
     *          mat 为空时返回空向量
     *  \note   该因子自逆（(-1)^(x+y) 的平方为 1），因此 IDFT/IFFT 之后
     *           需再乘一次同样的因子才能还原图像，参见 sample/ch04/P162F4_30.cpp
     *  \note   通道数不是 1/3/4 时抛出 cv::Exception（StsBadArg）
     *  \sa     MatToVector2D, Fourier::FFT, Fourier::DFT
     */
    std::vector<std::vector<double>> MatToPreCenteredVector2D(const cv::Mat& mat);

    cv::Mat CreateMatU8ByVector2D(const std::vector<std::vector<double>>& src, bool normalize = true);

} // namespace IPL
