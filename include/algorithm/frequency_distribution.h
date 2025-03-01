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

    /** \brief Geneate Ideal bandstop filters.
     *  \param[in] rows the height of filter
     *  \param[in] cols the width of filter
     *  \param[in] D0 cut-off frequency
     *  \param[in] W bandwidth
     *  \return geneated filter, a two-dimensional vector
     */
    std::vector<std::vector<double>> IBSF(int rows, int cols, double D0, double W);

    /** \brief Geneate B bandstop filters.
     *  \param[in] rows the height of filter
     *  \param[in] cols the width of filter
     *  \param[in] D0 cut-off frequency
     *  \param[in] W bandwidth
     *  \param[in] n the order of filter
     *  \return geneated filter, a two-dimensional vector
     */
    std::vector<std::vector<double>> BBSF(int rows, int cols, double D0, double W, int n = 2);

    /** \brief Geneate Gaussian bandstop filters.
     *  \param[in] rows the height of filter
     *  \param[in] cols the width of filter
     *  \param[in] D0 cut-off frequency
     *  \param[in] W bandwidth
     *  \return geneated filter, a two-dimensional vector
     */
    std::vector<std::vector<double>> GBSF(int rows, int cols, double D0, double W);

    /** \brief Geneate Ideal band-pass filters.
     *  \param[in] rows the height of filter
     *  \param[in] cols the width of filter
     *  \param[in] D0 cut-off frequency
     *  \param[in] W bandwidth
     *  \return geneated filter, a two-dimensional vector
     */
    std::vector<std::vector<double>> IBPF(int rows, int cols, double D0, double W);

    /** \brief Geneate B band-pass filters.
     *  \param[in] rows the height of filter
     *  \param[in] cols the width of filter
     *  \param[in] D0 cut-off frequency
     *  \param[in] W bandwidth
     *  \param[in] n the order of filter
     *  \return geneated filter, a two-dimensional vector
     */
    std::vector<std::vector<double>> BBPF(int rows, int cols, double D0, double W, int n = 2);

    /** \brief Geneate Gaussian band-pass filters.
     *  \param[in] rows the height of filter
     *  \param[in] cols the width of filter
     *  \param[in] D0 cut-off frequency
     *  \param[in] W bandwidth
     *  \return geneated filter, a two-dimensional vector
     */
    std::vector<std::vector<double>> GBPF(int rows, int cols, double D0, double W);

    /** \brief Geneate B bandstop notch filter.
     *  \param[in] rows the height of filter
     *  \param[in] cols the width of filter
     *  \param[in] D0s cut-off frequency
     *  \param[in] uv_ks off-centering
     *  \return geneated filter, a two-dimensional vector
     */
    std::vector<std::vector<double>> NBSF(int rows, int cols, std::vector<double> D0s,
                                          std::vector<std::pair<int, int>> uv_ks, int n = 2);

    /** \brief Geneate B band-pass notch filter.
     *  \param[in] rows the height of filter
     *  \param[in] cols the width of filter
     *  \param[in] D0 cut-off frequency
     *  \param[in] uv_ks off-centering
     *  \return geneated filter, a two-dimensional vector
     */
    std::vector<std::vector<double>> NBPF(int rows, int cols, std::vector<double> D0s,
                                          std::vector<std::pair<int, int>> uv_ks, int n = 2);

    class Point
    {
      public:
        Point() = default;
        Point(double x, double y) : _x(x), _y(y)
        {
        }
        ~Point()
        {
        }
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

} // namespace IPL

#endif //__FREQUENCY_DISTRIBUTION_H__
