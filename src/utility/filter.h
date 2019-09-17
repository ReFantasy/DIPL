/************************************************************************
 *
 *  自定义图像类型与OpenCV图像类型转换
 *
 ***********************************************************************/
#ifndef __FILTER_H__
#define __FILTER_H__
#include <vector>
#include <string>
#include "../algorithm/algorithm.hpp"
#include "image_convert.h"
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;


namespace IPL
{
	// 傅里叶滤波
	class FourierFilter
	{
		using Complex2D = vector<vector<std::complex<double>>>;
		
	public:
		FourierFilter() = default;
		Mat operator()(const Mat &src, const vector<vector<double>> &gauss, int ft_type = 0);

	private:
		vector<vector<double>> ImageData(const Mat &img);
		vector<vector<double>> ConvertToImage(const Complex2D&);
		Mat Out8UC1(const vector<vector<double>> &d);

	private:
		Fourier fourier;
		vector<vector<std::complex<double>>> _src_fourier_res;
		vector<vector<std::complex<double>>> _dst_fourier_res;

		vector<vector<std::complex<double>>> filter(const vector<vector<std::complex<double>>> &fourier, const vector<vector<double>> &gauss);

	};


	void OpencvFouier(Mat srcImage, std::string name);

	// 归一化的二维浮点数组转为CV_8UC1类型图像
	cv::Mat NormalizeVec2DToMat(const vector<vector<double>> &vec2d);

	// 归一化的二维浮点数组转为CV_8UC1类型图像
	cv::Mat ShowFourier(const vector<vector<std::complex<double>>> &vec2d);
	
	/** \brief Arithmetic mean filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \return the filtered image
	 */
	cv::Mat BlurArithmetic(const cv::Mat &_src, int kern_size = 3);

	/** \brief Geometry mean filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \return the filtered image
	 */
	cv::Mat BlurGeometry(const cv::Mat &_src, int kern_size = 3);

	/** \brief Harmonic mean filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \return the filtered image
	 */
	cv::Mat BlurHarmonic(const Mat &_src, int kern_size = 3);

	/** \brief Inverse Harmonic mean filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \parem[in] Q the order of the filter
	 *  \return the filtered image
	 */
	cv::Mat BlurInverseHarmonic(const Mat &_src, int kern_size, double Q = 0);

	/** \brief Median filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \return the filtered image
	 */
	cv::Mat BlurMedian(const Mat &_src, int kern_size = 3);

	/** \brief MaxMin filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \param[in] type 0:min 1:max
	 *  \return the filtered image
	 */
	cv::Mat BlurMaxMin(const Mat &_src, int kern_size = 3, int type = 0);

	/** \brief Middle filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \return the filtered image
	 */
	cv::Mat BlurMiddle(const Mat &_src, int kern_size = 3);

	/** \brief Modified alpha mean filter
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \param[in] d the number of dropped pixel
	 *  \return the filtered image
	 */
	cv::Mat BlurModifiedAlpha(const Mat &_src, int kern_size, int d);
	



}
#endif//__FILTER_H__