/************************************************************************************************
 *
 *  The header file define some universal frequency filter
 *
 *  Author  : ReFantasy
 *  Date    : 2019-08-22
 *  Contact : 309741309@qq.com
 *
 ***********************************************************************************************/
#ifndef __FREQUENCY_DISTRIBUTION_H__
#define __FREQUENCY_DISTRIBUTION_H__

#include <vector>

namespace IPL
{
	/** \brief Geneate B low-pass filter.
	 *  \param[in] rows the height of filter
	 *  \param[in] cols the width of filter
	 *  \param[in] D0 cut-off frequency
	 *  \param[in] n the order of filter
	 *  \return geneated filter, a two-dimensional vector
	 */
	std::vector<std::vector<double>> BLPF(int rows, int cols, double D0, int n = 2);

	/** \brief Geneate B high-pass filter.
	 *  \param[in] rows the height of filter
	 *  \param[in] cols the width of filter
	 *  \param[in] D0 cut-off frequency
	 *  \param[in] n the order of filter
	 *  \return geneated filter, a two-dimensional vector
	 */
	std::vector<std::vector<double>> BHPF(int rows, int cols, double D0, int n = 2);


	/** \brief Geneate Gaussian low-pass filter.
	 *  \param[in] rows the height of filter
	 *  \param[in] cols the width of filter
	 *  \param[in] D0 cut-off frequency
	 *  \return geneated filter, a two-dimensional vector
	 */
	std::vector<std::vector<double>> GLPF(int rows, int cols, double D0);

	/** \brief Geneate Gaussian high-pass filter.
	 *  \param[in] rows the height of filter
	 *  \param[in] cols the width of filter
	 *  \param[in] D0 cut-off frequency
	 *  \return geneated filter, a two-dimensional vector
	 */
	std::vector<std::vector<double>> GHPF(int rows, int cols, double D0);
	
	/** \brief Geneate Ideal low-pass filter.
	 *  \param[in] rows the height of filter
	 *  \param[in] cols the width of filter
	 *  \param[in] D0 cut-off frequency
	 *  \return geneated filter, a two-dimensional vector
	 */
	std::vector<std::vector<double>> ILPF(int rows, int cols, double D0);
	
	/** \brief Geneate Ideal high-pass filter.
	 *  \param[in] rows the height of filter
	 *  \param[in] cols the width of filter
	 *  \param[in] D0 cut-off frequency
	 *  \return geneated filter, a two-dimensional vector
	 */
	std::vector<std::vector<double>> IHPF(int rows, int cols, double D0);





	

	class Point
	{
	public:
		Point() = default;
		Point(double x, double y) :_x(x), _y(y) {}
		~Point() {}
		double _x;
		double _y;
	};

    /** \brief Compute the distance between two points.
     *  \param[in] p1 the first point
     *  \param[in] p2 the second point
     *  \return the distance between p1 and p2
     */
	double Distance(const Point &p1, const Point &p2);


	

	std::vector<std::vector<double>> MakeVector2D(int rows, int cols);

}

#endif//__FREQUENCY_DISTRIBUTION_H__

