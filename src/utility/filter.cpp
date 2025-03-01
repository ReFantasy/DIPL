#include "filter.h"
#include "image_convert.h"
#include "spatial_filter.h"

using namespace cv;
namespace IPL
{
    cv::Mat FourierFilter::operator()(const cv::Mat &src, const vector<vector<double>> &gauss,
                                      int ft_type)
    {
        assert(src.type() == CV_8UC1);

        // FFT
        if (ft_type == 0)
        {

            int rows = src.rows;
            int cols = src.cols;
            auto src_data = ImageData(src);

            // 傅里叶变换
            _src_fourier_res = fourier.FFT(src_data);

            // 频率域滤波
            _dst_fourier_res = filter(_src_fourier_res, gauss);

            // 返回空间域
            auto _dst_data = fourier.IFFT(_dst_fourier_res);

            // 输出图像
            auto dst_image_data = ConvertToImage(_dst_data);
            auto res = Out8UC1(dst_image_data);

            return res;
        }
        // DFT
        else
        {
            int rows = src.rows;
            int cols = src.cols;
            auto src_data = ImageData(src);

            // 傅里叶变换
            _src_fourier_res = fourier.DFT(src_data);

            // 频率域滤波
            _dst_fourier_res = filter(_src_fourier_res, gauss);

            // 返回空间域
            auto _dst_data = fourier.IDFT(_dst_fourier_res);

            // 输出图像
            auto dst_image_data = ConvertToImage(_dst_data);
            return Out8UC1(dst_image_data);
        }
    }

    void OpencvFouier(cv::Mat srcImage, std::string name)
    {
        // 2.将输入图像延扩到最佳尺寸，边界用0补充
        int m = getOptimalDFTSize(srcImage.rows);
        int n = getOptimalDFTSize(srcImage.cols);
        // 将添加的像素初始化为0。
        cv::Mat padded;
        copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols,
                       BORDER_CONSTANT, Scalar::all(0));

        // 3.为傅里叶变换的结果（实部和虚部）分配空间。
        // 将planes数组组合合并成一个多通道的数组complexI
        Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
        Mat complexI;
        merge(planes, 2, complexI);

        // 4.进行离散傅里叶变换
        dft(complexI, complexI);

        // 5.将复数转换为幅值，即 log(1+sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
        split(complexI, planes); // 将多通道数组complexI分离成几个单通道数组，[0]=Re,[1]=Im
        magnitude(planes[0], planes[1], planes[0]); // planes[0] = magnitude
        Mat magnitudeImage = planes[0];

        // 6.进行对数尺度（logarithmic scale）缩放
        magnitudeImage += Scalar::all(1);
        log(magnitudeImage, magnitudeImage); // 求自然对数

        // 7.剪切和重分布幅度图象限
        // 若有奇数行或奇数列，进行频谱裁剪
        magnitudeImage =
            magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));

        // 重新排列傅里叶图像中的象限，使得原点位于图像中心
        int cx = magnitudeImage.cols / 2;
        int cy = magnitudeImage.rows / 2;
        Mat q0(magnitudeImage, Rect(0, 0, cx, cy));   // ROI区域的左上
        Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));  // ROI区域的右上
        Mat q2(magnitudeImage, Rect(0, cy, cx, cy));  // ROI区域的左下
        Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); // ROI区域的右下
        // 交换象限（左上与右下进行交换）
        Mat tmp;
        q0.copyTo(tmp);
        q3.copyTo(q0);
        tmp.copyTo(q3);
        // 交换象限（右上与左下进行交换）
        q1.copyTo(tmp);
        q2.copyTo(q1);
        tmp.copyTo(q2);

        // 8.归一化，用0到1之间的浮点值将矩阵变换为可视化的图像格式
        normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

        // 9.显示效果图
        if (!name.empty())
        {
            imshow(name, magnitudeImage);
        }
        else
        {

            imshow("OpenCV fourier", magnitudeImage);
        }
    }

    vector<vector<double>> FourierFilter::ImageData(const Mat &img)
    {
        vector<vector<double>> src_data(img.rows, vector<double>(img.cols, 0));
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                src_data[i][j] = img.data[i * img.cols + j] * pow(-1, i + j);
            }
        }

        return src_data;
    }

    vector<vector<double>> FourierFilter::ConvertToImage(const Complex2D &dst_fourier)
    {
        int rows = dst_fourier.size();
        int cols = dst_fourier[0].size();

        vector<vector<double>> dst_data(rows, vector<double>(cols, 0));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                dst_data[i][j] = dst_fourier[i][j].real() * pow(-1, i + j);
            }
        }

        return dst_data;
    }

    cv::Mat FourierFilter::Out8UC1(const vector<vector<double>> &d)
    {
        int rows = d.size();
        int cols = d[0].size();

        Mat dst(rows, cols, CV_8UC1);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                double tmp = 0;

                tmp = d[i][j];
                tmp = (tmp > 255 ? 255 : tmp);
                tmp = (tmp < 0 ? 0 : tmp);
                dst.data[i * cols + j] = tmp;
            }
        }

        return dst;
    }

    vector<vector<std::complex<double>>> FourierFilter::filter(
        const vector<vector<std::complex<double>>> &fourier,
        const vector<vector<double>> &gauss)
    {
        int rows = fourier.size();
        int cols = fourier[0].size();

        vector<vector<std::complex<double>>> tmp(rows, vector<std::complex<double>>(cols, 0));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                tmp[i][j] = gauss[i][j] * fourier[i][j];
            }
        }

        return tmp;
    }

    cv::Mat NormalizeVec2DToMat(const vector<vector<double>> &vec2d)
    {
        assert(vec2d.size() > 0);
        assert(vec2d[0].size() > 0);
        int rows = vec2d.size();
        int cols = vec2d[0].size();
        cv::Mat dst(rows, cols, CV_64FC1);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {

                dst.at<double>(i, j) = vec2d[i][j];
            }
        }
        normalize(dst, dst, 0, 1, NORM_MINMAX);
        dst.convertTo(dst, CV_8UC1, 255);
        return dst;
    }

    cv::Mat ShowFourier(const vector<vector<std::complex<double>>> &vec2d)
    {
        assert(vec2d.size() > 0);
        assert(vec2d[0].size() > 0);
        int rows = vec2d.size();
        int cols = vec2d[0].size();
        cv::Mat dst(rows, cols, CV_64FC1);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {

                dst.at<double>(i, j) = std::log(1 + std::abs(vec2d[i][j]));
            }
        }
        normalize(dst, dst, 0, 1, NORM_MINMAX);
        dst.convertTo(dst, CV_8UC1, 255);
        return dst;
    }

    cv::Mat BlurArithmetic(const cv::Mat &_src, int kern_size)
    {
        auto src = IPL::Mat2Vector2D(_src);
        auto _blur = BlurArithmetic(src, kern_size);
        return NormalizeVec2DToMat(_blur);
    }

    cv::Mat BlurGeometry(const cv::Mat &_src, int kern_size)
    {
        auto src = IPL::Mat2Vector2D(_src);
        auto _blur = BlurGeometry(src, kern_size);
        return NormalizeVec2DToMat(_blur);
    }

    cv::Mat BlurHarmonic(const Mat &_src, int kern_size)
    {
        auto src = IPL::Mat2Vector2D(_src);
        auto _blur = BlurHarmonic(src, kern_size);
        return NormalizeVec2DToMat(_blur);
    }

    cv::Mat BlurInverseHarmonic(const Mat &_src, int kern_size, double Q)
    {
        auto src = IPL::Mat2Vector2D(_src);
        auto _blur = BlurInverseHarmonic(src, kern_size, Q);
        return NormalizeVec2DToMat(_blur);
    }

    cv::Mat BlurMedian(const Mat &_src, int kern_size)
    {
        auto src = IPL::Mat2Vector2D(_src);
        auto _blur = BlurMedian(src, kern_size);
        return NormalizeVec2DToMat(_blur);
    }

    cv::Mat BlurMaxMin(const Mat &_src, int kern_size, int type)
    {
        auto src = IPL::Mat2Vector2D(_src);
        auto _blur = BlurMaxMin(src, kern_size, type);
        return NormalizeVec2DToMat(_blur);
    }

    cv::Mat BlurMiddle(const Mat &_src, int kern_size /*= 3*/)
    {
        auto src = IPL::Mat2Vector2D(_src);
        auto _blur = BlurMiddle(src, kern_size);
        return NormalizeVec2DToMat(_blur);
    }

    cv::Mat BlurModifiedAlpha(const Mat &_src, int kern_size, int d)
    {
        auto src = IPL::Mat2Vector2D(_src);
        auto _blur = BlurModifiedAlpha(src, kern_size, d);
        return NormalizeVec2DToMat(_blur);
    }

} // namespace IPL
