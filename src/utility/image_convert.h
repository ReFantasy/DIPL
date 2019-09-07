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

	/** \brief Mat to std::vector<std::vector<double>> g(x,y) = f(x,y)
	 *  \param[in] Mat
	 *  \param[out] std::vector<std::vector<double>>
	 */
	std::vector<std::vector<double>> Mat2Vector2D(const cv::Mat &mat);
	
	/** \brief Mat to std::vector<std::vector<double>> g(x,y) = f(x,y)*(-1)^(x+y)
	 *  \param[in] Mat
	 *  \param[out] std::vector<std::vector<double>>
	 */
	std::vector<std::vector<double>> Mat2CentreVector2D(const cv::Mat &mat);
	
	/** \brief std::vector<std::vector<complex<double>>> to Mat
	 *  \param[in] std::vector<std::vector<complex<double>>>
	 *  \param[out] Mat
	 */
	cv::Mat VectorComplex2D2Mat(std::vector<std::vector<std::complex<double>>> &src);

}



#endif//__IMAGE_CONVERT_H__