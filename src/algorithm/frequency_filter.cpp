#include "frequency_filter.h"
#include <cmath>

namespace IPL
{

	
	

	std::vector<std::vector<double>> BLPF(int rows, int cols, double D0, int n)
	{
		int centre_x = rows / 2;
		int centre_y = cols / 2;

		auto blpf = MakeVector2D(rows, cols);
		
		for (int u = 0; u < rows; u++)
		{
			for (int v = 0; v < cols; v++)
			{
				double Duv = Distance(Point(u, v), Point(centre_x, centre_y));
				blpf[u][v] = 1.0 / (1 + std::pow(Duv / D0, 2 * n));
			}
		}

		return blpf;
	}


	std::vector<std::vector<double>> BHPF(int rows, int cols, double D0, int n /*= 2*/)
	{
		int centre_x = rows / 2;
		int centre_y = cols / 2;

		auto bhpf = MakeVector2D(rows, cols);

		for (int u = 0; u < rows; u++)
		{
			for (int v = 0; v < cols; v++)
			{
				double Duv = Distance(Point(u, v), Point(centre_x, centre_y));
				bhpf[u][v] = 1.0 / (1 + std::pow(D0 / Duv, 2 * n));
			}
		}

		return bhpf;
	}

	std::vector<std::vector<double>> GLPF(int rows, int cols, double D0)
	{
		int centre_x = rows / 2;
		int centre_y = cols / 2;

		auto glpf = MakeVector2D(rows, cols);

		for (int u = 0; u < rows; u++)
		{
			for (int v = 0; v < cols; v++)
			{
				double Duv = Distance(Point(u, v), Point(centre_x, centre_y));
				glpf[u][v] = std::exp(-std::pow(Duv, 2) / (2.0*std::pow(D0, 2)));
			}
		}

		return glpf;
	}

	std::vector<std::vector<double>> GHPF(int rows, int cols, double D0)
	{
		auto ghpf = GLPF(rows, cols, D0);
		for (auto &e : ghpf)
			for (auto &i : e)
				i = 1 - i;
		return ghpf;
	}
	
	std::vector<std::vector<double>> ILPF(int rows, int cols, double D0)
	{
		int centre_x = rows / 2;
		int centre_y = cols / 2;

		auto ilpf = MakeVector2D(rows, cols);

		for (int u = 0; u < rows; u++)
		{
			for (int v = 0; v < cols; v++)
			{
				double Duv = Distance(Point(u, v), Point(centre_x, centre_y));
				if(Duv<=D0)
				    ilpf[u][v] = 1;
				else
					ilpf[u][v] = 0;
			}
		}

		return ilpf;
	}
	
	

	std::vector<std::vector<double>> MakeVector2D(int rows, int cols)
	{
		return std::vector<std::vector<double>>(rows, std::vector<double>(cols, 0));
	}


	double Distance(const Point &p1, const Point &p2)
	{
		return std::sqrt(std::pow(p1._x - p2._x, 2) + std::pow(p1._y - p2._y, 2));
	}

}
