/************************************************************************************************
 *
 *  
 *  Definition gaussian function:
 *
 *     f(x) = a*e^( -(x-b)^2/(2*c^2) )                               // one-dimensional
 *
 *   f(x,y) = A*e^(-( (x-a)^2/(2*sigmax^2)+(y-b)^2/(x*sigmay^2) ) )  // two-dimension
 *
 *  More details:  https://blog.csdn.net/jorg_zhao/article/details/52687448
 *
 ***********************************************************************************************/
#ifndef __GAUSSKERNEL_H__
#define __GAUSSKERNEL_H__
#include <vector>

/* 
 * generate one-dimensional gaussian kernel
 *
 * param[in] size the length of gaussian kernel
 * param[in] sigma the width of gaussian bell
 * param[in] a the amplitude of gaussian kernel
 *
 */
std::vector<double> GenGaussianKernel(int size, double sigma, double a);


/*
 * generate two-dimensional gaussian kernel
 *
 * param[in] rows the height of gaussian kernel
 * param[in] cols the width of gaussian kernel
 * param[in] A the amplitude of gaussian kernel
 * param[in] sigma_x the width of gaussian bell in the x direction
 * param[in] sigma_y the width of gaussian bell in the y direction
 *
 */
std::vector<std::vector<double>> GenGaussianKernel(int rows,int cols, double sigma_x, double sigma_y, double A);




#endif//__GAUSSKERNEL_H__

