/************************************************************************
 *     Mat��ʹ���ά����֮���ת��
 ************************************************************************/
#ifndef __IMAGE_CONVERT_H__
#define __IMAGE_CONVERT_H__
#include "opencv2/opencv.hpp"
#include <complex>
#include <vector>

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

} // namespace IPL

#endif //__IMAGE_CONVERT_H__
