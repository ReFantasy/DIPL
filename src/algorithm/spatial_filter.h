/*
 *  ¿Õ¼äÂË²¨
 *
 */


#ifndef __SPATIAL_FILTER_H__
#define __SPATIAL_FILTER_H__
#include "algorithm.hpp"
#include <cmath>
#include <vector>
namespace IPL
{
	
	std::vector<std::vector<double>> PaddingImage(const std::vector<std::vector<double>> &src,
		int left, int right, int top, int bottom);

	/** \brief Padding image whose size is a*b to a new image whose size is (a+2n)*(b+2n)
	 *  \param[in] src image data
	 *  \param[in] n the size to pad image
	 *  \return the padded image
	 */
	std::vector<std::vector<double>> PaddingImage(const std::vector<std::vector<double>> &src, int n);

	/** \brief Arithmetic mean filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \return the filtered image
	 */
	std::vector<std::vector<double>> BlurArithmetic(const std::vector<std::vector<double>> &src, int kern_size);

	/** \brief Geometry mean filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \return the filtered image
	 */
	std::vector<std::vector<double>> BlurGeometry(const std::vector<std::vector<double>> &src, int kern_size);

	/** \brief Harmonic mean filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \return the filtered image
	 */
	std::vector<std::vector<double>> BlurHarmonic(const std::vector<std::vector<double>> &src, int kern_size);

	/** \brief Inverse Harmonic mean filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \parem[in] Q the order of the filter
	 *  \return the filtered image
	 */
	std::vector<std::vector<double>> BlurInverseHarmonic(const std::vector<std::vector<double>> &src, int kern_size, double Q);

	/** \brief Median filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \return the filtered image
	 */
	std::vector<std::vector<double>> BlurMedian(const std::vector<std::vector<double>> &src, int kern_size);

	/** \brief MaxMin filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \param[in] type 0:min 1:max
	 *  \return the filtered image
	 */
	std::vector<std::vector<double>> BlurMaxMin(const std::vector<std::vector<double>> &src, int kern_size, int type = 0);

	/** \brief Middle filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \return the filtered image
	 */
	std::vector<std::vector<double>> BlurMiddle(const std::vector<std::vector<double>> &src, int kern_size);

	/** \brief Modified alpha mean filter
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \param[in] d the number of dropped pixel
	 *  \return the filtered image
	 */
	std::vector<std::vector<double>> BlurModifiedAlpha(const std::vector<std::vector<double>> &src, int kern_size, int d);

	std::vector<std::vector<double>> NearestNeighborInterpolation(const std::vector<std::vector<double>> &src, 
		                                                          int new_rows, int new_cols);
	
	bool IsOdd(int num);
	
}


#endif//__SPATIAL_FILTER_H__