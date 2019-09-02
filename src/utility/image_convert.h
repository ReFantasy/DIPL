/************************************************************************
 *     Mat类和纯二维数组之间的转换                                                                 
 ************************************************************************/
#ifndef __IMAGE_CONVERT_H__
#define __IMAGE_CONVERT_H__
#include <vector>
#include <complex>
#include "opencv2/opencv.hpp"

namespace IPL
{

	/** \brief std::vector<std::vector<double>> to Mat
	 *  \param[in] two-dimensional double type array
	 *  \param[out] cv::Mat 8UC1
	 */
	//void ImageConvert(const std::vector<std::vector<double>> &vec_2d_double, cv::Mat &dst);



	/** \brief std::vector<std::vector<std::complex<double>>> to Mat
	 *  \param[in] two-dimensional complex type array
	 *  \param[out] cv::Mat 8UC1
	 */
	//void ImageConvert(const std::vector<std::vector<std::complex<double>>> &vec_2d_complex, cv::Mat &dst);



	/** \brief Mat to std::vector<std::vector<double>>
	 *  \param[in] Mat
	 *  \param[out] std::vector<std::vector<double>>
	 */
	std::vector<std::vector<double>> ImageConvert(const cv::Mat &mat);



	/** \brief Mat to std::vector<std::vector<std::complex<double>>>
	 *  \param[in] Mat
	 *  \param[out] std::vector<std::vector<std::complex<double>>>
	 */
	//void ImageConvert(const cv::Mat &mat, std::vector<std::vector<std::complex<double>>> &dst);
}



#endif//__IMAGE_CONVERT_H__