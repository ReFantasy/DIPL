#include "wavelet_transform.h"



std::vector<std::vector<double>> IPL::PryUp(const std::vector<std::vector<double>> &src)
{
	int rows = src.size() * 2;
	int cols = src[0].size() * 2;
	auto res = IPL::MakeVector2D(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if ((i % 2 == 0) && (j % 2 == 0))
			{
				res[i][j] = src[i / 2][j / 2];
			}
			else
			{
				res[i][j] = 0;
			}
		}
	}

	return res;
}

std::vector<std::vector<double>> IPL::PryDown(const std::vector<std::vector<double>> &src)
{
	int rows = src.size();
	int cols = src[0].size();

	auto res = IPL::MakeVector2D(rows / 2, cols / 2);

	for (int i = 0; i < res.size(); i++)
	{
		for (int j = 0; j < res[0].size(); j++)
		{

			res[i][j] = src[i * 2][j * 2];
		}
	}

	return res;
}

void IPL::PyramidExample(const std::vector<std::vector<double>> &src, std::vector<std::vector<double>> &approximate, std::vector<std::vector<double>> &residual)
{
	int rows = src.size();
	int cols = src[0].size();


	// ���ɽ���ͼ
	auto s = IPL::BlurArithmetic(src, 5);
	approximate = PryDown(s);

	// �ϲ��������в�ֵ�˲�
	// �ϲ�������һ���õ���ͼ��approximate�ߴ��������� ��������ؼ����0
	// ��ֵ�˲�������Ϊ0��λ�ø���ԭͼ��approximate���в�ֵ
	// �����������ڲ�ֵ����������������
	auto indicate = IPL::NearestNeighborInterpolation(approximate, rows, cols);

	residual = IPL::MakeVector2D(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			residual[i][j] = src[i][j] - indicate[i][j];
		}
	}
}
