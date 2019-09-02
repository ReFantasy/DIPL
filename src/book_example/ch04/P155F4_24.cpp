#include <iostream>      
#include <vector>
#include <iterator>
#include <random>
#include <chrono>
#include "opencv2/opencv.hpp"
#include "utility/fourier_filter.h"
#include "utility/Timer.h"
#include "utility/Rand.h"
#include "utility/image_convert.h"
#include "algorithm/Fourier.h"

using namespace std;

void OpencvFouier(Mat srcImage);

int main(int argc, char *argv[])
{
	if (argc < 2)
		return -1;
	Mat src = imread(argv[1], 0);
	int rows = src.rows;
	int cols = src.cols;
	IPL::Fourier fourier;

	auto img = vector<vector<double>>(rows, vector<double>(cols, 0));
	for (int i = 0; i < rows; i++)
		for (int j = 1; j < cols; j++)
		{
			img[i][j] = src.data[i*cols + j] * pow(-1, i + j);
		}


	auto fres = IPL::Fourier::FFT(img);

	//Mat c(rows, cols, CV_8UC1);
	//for (int i = 0; i < rows; i++)
	//	for (int j = 1; j < cols; j++)
	//	{
	//		int tmp =sqrt(fres[i][j].real()*fres[i][j].real()+ fres[i][j].imag()*fres[i][j].imag());
	//		tmp = tmp < 0 ? 0 : tmp;
	//		tmp = tmp > 255 ? 255 : tmp;
	//		c.data[i*cols + j] = tmp;
	//		//c.at<double>(i, j) = abs(fres[i][j]);
	//	}
	////normalize(c, c, 0, 1);

	Mat d(rows, cols, CV_64FC1);
	for(int i = 0;i<rows;i++)
		for (int j = 1; j < cols; j++)
		{
			double tmp = log(1+abs(fres[i][j]));
			//double tmp = abs(fres[i][j]);
			d.at<double>(i, j) = tmp;
			//d.data[i*cols + j] = tmp;
		}
	normalize(d, d, 0, 1, NORM_MINMAX);
	//imshow("c", c);
	imshow("d", d);

	OpencvFouier(src);
	
	waitKey();
	return 0;
}

void OpencvFouier(Mat srcImage)
{
	// 2.������ͼ����������ѳߴ磬�߽���0����
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);
	// ����ӵ����س�ʼ��Ϊ0��
	Mat padded;
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	// 3.Ϊ����Ҷ�任�Ľ����ʵ�����鲿������ռ䡣
	// ��planes������Ϻϲ���һ����ͨ��������complexI
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(),CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);

	// 4.������ɢ����Ҷ�任
	dft(complexI, complexI);

	// 5.������ת��Ϊ��ֵ���� log(1+sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
	split(complexI, planes);    //����ͨ������complexI����ɼ�����ͨ�����飬[0]=Re,[1]=Im
	magnitude(planes[0], planes[1], planes[0]); //planes[0] = magnitude
	Mat magnitudeImage = planes[0];

	// 6.���ж����߶ȣ�logarithmic scale������
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);    //����Ȼ����

	// 7.���к��طֲ�����ͼ����
	//���������л������У�����Ƶ�ײü�
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));

	// �������и���Ҷͼ���е����ޣ�ʹ��ԭ��λ��ͼ������
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));     //ROI���������
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));    //ROI���������
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));    //ROI���������
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));   //ROI���������
	//�������ޣ����������½��н�����
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//�������ޣ����������½��н�����
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	// 8.��һ������0��1֮��ĸ���ֵ������任Ϊ���ӻ���ͼ���ʽ
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

	// 9.��ʾЧ��ͼ
	imshow("OpenCV Ƶ�׷�ֵ", magnitudeImage);
}

