/*
 *  ¿Õ¼äÂË²¨
 *
 */


#ifndef __SPATIAL_FILTER_H__
#define __SPATIAL_FILTER_H__
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
	std::vector<std::vector<double>> MeanBlurArithmetic(const std::vector<std::vector<double>> &src, int kern_size);

	/** \brief Geometry mean filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \return the filtered image
	 */
	std::vector<std::vector<double>> MeanBlurGeometry(const std::vector<std::vector<double>> &src, int kern_size);

	/** \brief Harmonic mean filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \return the filtered image
	 */
	std::vector<std::vector<double>> MeanBlurHarmonic(const std::vector<std::vector<double>> &src, int kern_size);

	/** \brief Inverse Harmonic mean filtering
	 *  \param[in] src image data
	 *  \param[in] kern_size the size of filter
	 *  \parem[in] Q the order of the filter
	 *  \return the filtered image
	 */
	std::vector<std::vector<double>> MeanBlurInverseHarmonic(const std::vector<std::vector<double>> &src, int kern_size, double Q);

	
	bool IsOdd(int num);
	
}


#endif//__SPATIAL_FILTER_H__