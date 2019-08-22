/************************************************************************************************
 *
 *  
 *  Gaussian pass filter
 *
 *
 ***********************************************************************************************/
#ifndef __GAUSSKERNEL_H__
#define __GAUSSKERNEL_H__
#include <vector>

/* 
 * generate one-dimensional gaussian low pass filter
 * define: f(x) = a*e^( -(x-b)^2/(2*c^2) )
 *
 * param[in] size the length of gaussian kernel
 * param[in] sigma the width of gaussian bell
 * param[in] a the amplitude of gaussian kernel
 *
 */
std::vector<double> GLPF(int size, double sigma, double a = 1);


/*
 * generate two-dimensional gaussian low pass filter
 * define: f(x,y) = A*e^(-( (x-a)^2/(2*sigmax^2)+(y-b)^2/(x*sigmay^2) ) )
 *
 * param[in] rows the height of gaussian kernel
 * param[in] cols the width of gaussian kernel
 * param[in] A the amplitude of gaussian kernel
 * param[in] sigma_x the width of gaussian bell in the x direction
 * param[in] sigma_y the width of gaussian bell in the y direction
 *
 */
std::vector<std::vector<double>> GLPF(int rows,int cols, double sigma_x, double sigma_y, double A = 1);




#endif//__GAUSSKERNEL_H__

