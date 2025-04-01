#include "frequency_distribution.h"
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

    std::vector<std::vector<double>> BHPF(int rows, int cols, double D0, int n)
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
                glpf[u][v] = std::exp(-std::pow(Duv, 2) / (2.0 * std::pow(D0, 2)));
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
                if (Duv <= D0)
                    ilpf[u][v] = 1;
                else
                    ilpf[u][v] = 0;
            }
        }

        return ilpf;
    }

    std::vector<std::vector<double>> IHPF(int rows, int cols, double D0)
    {
        int centre_x = rows / 2;
        int centre_y = cols / 2;

        auto ihpf = MakeVector2D(rows, cols);

        for (int u = 0; u < rows; u++)
        {
            for (int v = 0; v < cols; v++)
            {
                double Duv = Distance(Point(u, v), Point(centre_x, centre_y));
                if (Duv <= D0)
                    ihpf[u][v] = 0;
                else
                    ihpf[u][v] = 1;
            }
        }

        return ihpf;
    }

    std::vector<std::vector<double>> IBSF(int rows, int cols, double D0, double W)
    {
        int centre_x = rows / 2;
        int centre_y = cols / 2;

        auto ibsf = MakeVector2D(rows, cols);

        for (int u = 0; u < rows; u++)
        {
            for (int v = 0; v < cols; v++)
            {
                double Duv = Distance(Point(u, v), Point(centre_x, centre_y));

                if ((Duv >= D0 - W / 2) && (Duv <= D0 + W / 2))
                    ibsf[u][v] = 0;
                else
                    ibsf[u][v] = 1;
            }
        }

        return ibsf;
    }

    std::vector<std::vector<double>> BBSF(int rows, int cols, double D0, double W, int n)
    {
        int centre_x = rows / 2;
        int centre_y = cols / 2;

        auto bbsf = MakeVector2D(rows, cols);

        for (int u = 0; u < rows; u++)
        {
            for (int v = 0; v < cols; v++)
            {
                double Duv = Distance(Point(u, v), Point(centre_x, centre_y));

                bbsf[u][v] = 1.0 / (1 + pow(Duv * W / (Duv * Duv - D0 * D0), 2 * n));
            }
        }

        return bbsf;
    }

    std::vector<std::vector<double>> GBSF(int rows, int cols, double D0, double W)
    {
        int centre_x = rows / 2;
        int centre_y = cols / 2;

        auto gbsf = MakeVector2D(rows, cols);

        for (int u = 0; u < rows; u++)
        {
            for (int v = 0; v < cols; v++)
            {
                double Duv = Distance(Point(u, v), Point(centre_x, centre_y));

                double tmp = (Duv * Duv - D0 * D0) / Duv / W;
                gbsf[u][v] = 1 - exp(-pow(tmp, 2));
            }
        }

        return gbsf;
    }

    std::vector<std::vector<double>> IBPF(int rows, int cols, double D0, double W)
    {
        auto ibsf = IBSF(rows, cols, D0, W);
        for (auto &e : ibsf)
        {
            for (auto &i : e)
                i = 1 - i;
        }
        return ibsf;
    }

    std::vector<std::vector<double>> BBPF(int rows, int cols, double D0, double W,
                                          int n /*= 2*/)
    {
        auto bbsf = BBSF(rows, cols, D0, W);
        for (auto &e : bbsf)
        {
            for (auto &i : e)
                i = 1 - i;
        }
        return bbsf;
    }

    std::vector<std::vector<double>> GBPF(int rows, int cols, double D0, double W)
    {
        auto gbsf = GBSF(rows, cols, D0, W);
        for (auto &e : gbsf)
        {
            for (auto &i : e)
                i = 1 - i;
        }
        return gbsf;
    }

    std::vector<std::vector<double>> NBSF(int rows, int cols, std::vector<double> D0s,
                                          std::vector<std::pair<int, int>> uv_ks,
                                          int n /*= 2*/)
    {
        auto res = MakeVector2D(rows, cols);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                double res_value = 1.0;
                for (unsigned int k = 0; k < uv_ks.size(); k++)
                {
                    int u_k = uv_ks[k].first;
                    int v_k = uv_ks[k].second;

                    float dk = sqrt(pow((i - u_k), 2) + pow((j - v_k), 2));
                    float d_k = sqrt(pow((i + u_k), 2) + pow((j + v_k), 2));

                    float dst_dk = 1.0 / (1.0 + pow(D0s[k] / dk, 2 * n));
                    float dst_d_k = 1.0 / (1.0 + pow(D0s[k] / d_k, 2 * n));

                    res_value = dst_dk * dst_d_k * res_value;
                }
                res[i][j] = res_value;
            }
        }

        return res;

        // int M = rows;
        // int N = cols;
        // auto Dk = [&](int u, int v, int uk, int vk)
        //{
        //	return pow(pow((u - M / 2 - uk), 2) + pow((v - N / 2 - vk), 2), 0.5);
        // };
        // auto D_k = [&](int u, int v, int uk, int vk)
        //{
        //	return pow(pow((u - M / 2 + uk), 2) + pow((v - N / 2 + vk), 2), 0.5);
        // };

        //// 一个陷波对
        // auto NR = [&](int D0,  int uk, int vk)
        //{
        //	auto vec_2d = MakeVector2D(rows, cols);
        //	for (int i = 0; i < rows; i++)
        //	{
        //		for (int j = 0; j < cols; j++)
        //		{
        //			double tmp = (1.0 / (1 + pow(D0 / Dk(i, j, uk, vk), 2 * n)))*(1.0 / (1 +
        //pow(D0 / D_k(i, j, uk, vk), 2 * n))); 			vec_2d[i][j] = tmp;
        //		}
        //	}
        //	return vec_2d;
        // };
        // std::vector<std::vector<std::vector<double>>> trapped;
        // for (int i = 0; i < D0s.size(); i++)
        //{
        //	trapped.push_back(NR(D0s[i], uv_ks[i].first, uv_ks[i].second));
        // }

        // auto res = MakeVector2D(rows, cols);
        // for (int i = 0; i < rows; i++)
        //{
        //	for (int j = 0; j < cols; j++)
        //	{
        //		double tmp = 1;
        //		for (int k = 0; k < D0s.size(); k++)
        //		{
        //			tmp *= (trapped[k][i][j]);
        //		}
        //		res[i][j] = tmp;
        //	}
        // }

        // return res;
    }

    std::vector<std::vector<double>> NBPF(int rows, int cols, std::vector<double> D0s,
                                          std::vector<std::pair<int, int>> uv_ks,
                                          int n /*= 2*/)
    {
        auto res = NBSF(rows, cols, D0s, uv_ks, n);
        for (auto &e : res)
        {
            for (auto &i : e)
            {
                i = 1 - i;
            }
        }
        return res;
    }

    std::vector<std::vector<double>> MakeVector2D(int rows, int cols)
    {
        return std::vector<std::vector<double>>(rows, std::vector<double>(cols, 0));
    }

    double Distance(const Point &p1, const Point &p2)
    {
        return std::sqrt(std::pow(p1._x - p2._x, 2) + std::pow(p1._y - p2._y, 2));
    }

} // namespace IPL
