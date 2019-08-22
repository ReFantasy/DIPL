#include "GaussKernel.h"


std::vector<double> GLPF(int size, double sigma, double a)
{
	int centre = size / 2;
	std::vector<double> kernel(size, 0);

	for (int i = 0; i < size; i++)
	{
		double tmp = (i - centre)*(i - centre) / (2 * sigma*sigma);
		kernel[i] = a * exp(-tmp);
	}

	return kernel;
}

std::vector<std::vector<double>> GLPF(int rows, int cols, double sigma_x, double sigma_y, double A)
{
	std::vector<std::vector<double>> kernel(rows, std::vector<double>(cols, 0));

	int centre_x = rows / 2;
	int centre_y = cols / 2;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			double px = (i - centre_x)*(i - centre_x) / (2 * sigma_x*sigma_x);
			double py = (j - centre_y)*(j - centre_y) / (2 * sigma_y*sigma_y);
			kernel[i][j] = A*exp(-(px + py));
		}
	}
	return kernel;
}
