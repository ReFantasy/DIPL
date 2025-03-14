#include "spatial_filter.h"
#include "frequency_distribution.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>

std::vector<std::vector<double>>
IPL::PaddingImage(const std::vector<std::vector<double>>& src, int left, int right, int top, int bottom)
{
    assert(src.size() > 0);
    assert(src[0].size() > 0);
    int old_rows = src.size();
    int old_cols = src[0].size();
    int new_rows = old_rows + top + bottom;
    int new_cols = old_cols + left + right;

    std::vector<std::vector<double>> new_image(new_rows, std::vector<double>(new_cols, 0));

    // ����ԭʼ����
    for (int i = 0; i < old_rows; i++)
    {
        for (int j = 0; j < old_cols; j++)
        {
            new_image[i + top][j + left] = src[i][j];
        }
    }

    // �����Ե
    for (int i = 0; i < old_rows; i++)
    {
        // left
        for (int j = 0; j < left; j++)
        {
            new_image[i + top][j] = src[i][0];
        }
        // right
        for (int j = 0; j < right; j++)
        {
            new_image[i + top][j + left + old_cols] = src[i][old_cols - 1];
        }
    }

    for (int j = 0; j < new_cols; j++)
    {
        for (int i = 0; i < top; i++)
        {
            new_image[i][j] = new_image[top][j];
        }
        for (int i = 0; i < bottom; i++)
        {
            new_image[i + top + old_rows][j] = new_image[old_rows - 1][j];
        }
    }

    return new_image;
}

std::vector<std::vector<double>> IPL::PaddingImage(const std::vector<std::vector<double>>& src, int n)
{
    return PaddingImage(src, n, n, n, n);
}

std::vector<std::vector<double>> IPL::BlurArithmetic(const std::vector<std::vector<double>>& src, int kern_size)
{
    // �ж��˲��˴�С�Ƿ�Ϊ����
    if (!IsOdd(kern_size))
        kern_size += 1;

    // ��չͼ��߽�
    int  half_kern    = (kern_size - 1) / 2;
    auto image_padded = PaddingImage(src, half_kern);

    // ��ֵ�˲�
    int                              rows = src.size();
    int                              cols = src[0].size();
    std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));

    for (int i = half_kern; i < rows + half_kern; i++)
    {
        for (int j = half_kern; j < cols + half_kern; j++)
        {
            double tmp = 0;
            for (int m = i - half_kern; m <= i + half_kern; m++)
            {
                for (int n = j - half_kern; n <= j + half_kern; n++)
                {
                    tmp += image_padded[m][n];
                }
            }

            tmp /= (kern_size * kern_size);
            dst[i - half_kern][j - half_kern] = tmp;
        }
    }
    return dst;
}

std::vector<std::vector<double>> IPL::BlurGeometry(const std::vector<std::vector<double>>& src, int kern_size)
{
    // �ж��˲��˴�С�Ƿ�Ϊ����
    if (!IsOdd(kern_size))
        kern_size += 1;

    // ��չͼ��߽�
    int  half_kern    = (kern_size - 1) / 2;
    auto image_padded = PaddingImage(src, half_kern);

    // ��ֵ�˲�
    int                              rows = src.size();
    int                              cols = src[0].size();
    std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));

    for (int i = half_kern; i < rows + half_kern; i++)
    {
        for (int j = half_kern; j < cols + half_kern; j++)
        {
            double tmp = 1;
            for (int m = i - half_kern; m <= i + half_kern; m++)
            {
                for (int n = j - half_kern; n <= j + half_kern; n++)
                {
                    if (image_padded[m][n] != 0)
                        tmp *= image_padded[m][n];
                }
            }

            dst[i - half_kern][j - half_kern] = std::pow(tmp, 1.0 / (kern_size * kern_size));
        }
    }
    return dst;
}

std::vector<std::vector<double>> IPL::BlurHarmonic(const std::vector<std::vector<double>>& src, int kern_size)
{
    // �ж��˲��˴�С�Ƿ�Ϊ����
    if (!IsOdd(kern_size))
        kern_size += 1;

    // ��չͼ��߽�
    int  half_kern    = (kern_size - 1) / 2;
    auto image_padded = PaddingImage(src, half_kern);

    // ��ֵ�˲�
    int                              rows = src.size();
    int                              cols = src[0].size();
    std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));

    for (int i = half_kern; i < rows + half_kern; i++)
    {
        for (int j = half_kern; j < cols + half_kern; j++)
        {
            double tmp = 0;
            for (int m = i - half_kern; m <= i + half_kern; m++)
            {
                for (int n = j - half_kern; n <= j + half_kern; n++)
                {
                    tmp += 1.0 / image_padded[m][n];
                }
            }

            tmp                               = kern_size * kern_size / tmp;
            dst[i - half_kern][j - half_kern] = tmp;
        }
    }
    return dst;
}

std::vector<std::vector<double>>
IPL::BlurInverseHarmonic(const std::vector<std::vector<double>>& src, int kern_size, double Q)
{
    // �ж��˲��˴�С�Ƿ�Ϊ����
    if (!IsOdd(kern_size))
        kern_size += 1;

    // ��չͼ��߽�
    int  half_kern    = (kern_size - 1) / 2;
    auto image_padded = PaddingImage(src, half_kern);

    // ��ֵ�˲�
    int                              rows = src.size();
    int                              cols = src[0].size();
    std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));

    for (int i = half_kern; i < rows + half_kern; i++)
    {
        for (int j = half_kern; j < cols + half_kern; j++)
        {
            double tmp1 = 0;
            double tmp2 = 0;
            for (int m = i - half_kern; m <= i + half_kern; m++)
            {
                for (int n = j - half_kern; n <= j + half_kern; n++)
                {
                    tmp1 += std::pow(image_padded[m][n], Q + 1);
                    tmp2 += std::pow(image_padded[m][n], Q);
                }
            }

            dst[i - half_kern][j - half_kern] = tmp1 / tmp2;
        }
    }
    return dst;
}

std::vector<std::vector<double>> IPL::BlurMedian(const std::vector<std::vector<double>>& src, int kern_size)
{
    // �ж��˲��˴�С�Ƿ�Ϊ����
    if (!IsOdd(kern_size))
        kern_size += 1;

    // ��չͼ��߽�
    int  half_kern    = (kern_size - 1) / 2;
    auto image_padded = PaddingImage(src, half_kern);

    // ��ֵ�˲�
    int                              rows = src.size();
    int                              cols = src[0].size();
    std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));

    for (int i = half_kern; i < rows + half_kern; i++)
    {
        for (int j = half_kern; j < cols + half_kern; j++)
        {
            std::vector<double> tmps;
            for (int m = i - half_kern; m <= i + half_kern; m++)
            {
                for (int n = j - half_kern; n <= j + half_kern; n++)
                {
                    tmps.push_back(image_padded[m][n]);
                }
            }

            std::sort(tmps.begin(), tmps.end());
            dst[i - half_kern][j - half_kern] = tmps[tmps.size() / 2];
        }
    }
    return dst;
}

std::vector<std::vector<double>> IPL::BlurMaxMin(const std::vector<std::vector<double>>& src, int kern_size, int type)
{
    // �ж��˲��˴�С�Ƿ�Ϊ����
    if (!IsOdd(kern_size))
        kern_size += 1;

    // ��չͼ��߽�
    int  half_kern    = (kern_size - 1) / 2;
    auto image_padded = PaddingImage(src, half_kern);

    // ��ֵ�˲�
    int                              rows = src.size();
    int                              cols = src[0].size();
    std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));

    for (int i = half_kern; i < rows + half_kern; i++)
    {
        for (int j = half_kern; j < cols + half_kern; j++)
        {
            std::vector<double> tmps;
            for (int m = i - half_kern; m <= i + half_kern; m++)
            {
                for (int n = j - half_kern; n <= j + half_kern; n++)
                {
                    tmps.push_back(image_padded[m][n]);
                }
            }

            if (type == 0)
                dst[i - half_kern][j - half_kern] = *(std::min_element(tmps.begin(), tmps.end()));
            else
                dst[i - half_kern][j - half_kern] = *(std::max_element(tmps.begin(), tmps.end()));
        }
    }
    return dst;
}

std::vector<std::vector<double>> IPL::BlurMiddle(const std::vector<std::vector<double>>& src, int kern_size)
{
    // �ж��˲��˴�С�Ƿ�Ϊ����
    if (!IsOdd(kern_size))
        kern_size += 1;

    // ��չͼ��߽�
    int  half_kern    = (kern_size - 1) / 2;
    auto image_padded = PaddingImage(src, half_kern);

    // ��ֵ�˲�
    int                              rows = src.size();
    int                              cols = src[0].size();
    std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));

    for (int i = half_kern; i < rows + half_kern; i++)
    {
        for (int j = half_kern; j < cols + half_kern; j++)
        {
            std::vector<double> tmps;
            for (int m = i - half_kern; m <= i + half_kern; m++)
            {
                for (int n = j - half_kern; n <= j + half_kern; n++)
                {
                    tmps.push_back(image_padded[m][n]);
                }
            }

            double minv                       = *(std::min_element(tmps.begin(), tmps.end()));
            double maxv                       = *(std::max_element(tmps.begin(), tmps.end()));
            dst[i - half_kern][j - half_kern] = (minv + maxv) / 2;
        }
    }
    return dst;
}

std::vector<std::vector<double>>
IPL::BlurModifiedAlpha(const std::vector<std::vector<double>>& src, int kern_size, int d)
{
    // �ж��˲��˴�С�Ƿ�Ϊ����
    if (!IsOdd(kern_size))
        kern_size += 1;
    if (d >= kern_size * kern_size)
        d = kern_size * kern_size - 1;

    // ��չͼ��߽�
    int  half_kern    = (kern_size - 1) / 2;
    auto image_padded = PaddingImage(src, half_kern);

    // ��ֵ�˲�
    int                              rows = src.size();
    int                              cols = src[0].size();
    std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));

    for (int i = half_kern; i < rows + half_kern; i++)
    {
        for (int j = half_kern; j < cols + half_kern; j++)
        {
            std::vector<double> tmps;
            for (int m = i - half_kern; m <= i + half_kern; m++)
            {
                for (int n = j - half_kern; n <= j + half_kern; n++)
                {
                    tmps.push_back(image_padded[m][n]);
                }
            }
            std::sort(tmps.begin(), tmps.end());
            // ȥ��ǰ���d/2��Ԫ�أ��������ֵ
            double sum                        = std::accumulate(tmps.begin() + d / 2, tmps.end() - d / 2, 0);
            dst[i - half_kern][j - half_kern] = sum / (kern_size * kern_size - d);
        }
    }
    return dst;
}

std::vector<std::vector<double>>
IPL::NearestNeighborInterpolation(const std::vector<std::vector<double>>& src, int new_rows, int new_cols)
{
    int  rows = src.size();
    int  cols = src[0].size();
    auto res  = IPL::MakeVector2D(new_rows, new_cols);
    for (int i = 0; i < new_rows; i++)
    {
        for (int j = 0; j < new_cols; j++)
        {
            int r = std::round(i / (double)new_rows * rows);
            int c = std::round(j / (double)new_cols * cols);
            if (r >= rows)
                r = rows - 1;
            if (c >= cols)
                c = cols - 1;
            res[i][j] = src[r][c];
        }
    }

    return res;
}

bool IPL::IsOdd(int num) { return (num % 2); }
