#include <iostream>
#include "opencv2/opencv.hpp"
#include "Image.h"
#include "Filter.h"
#include "histogram.h"
using namespace std;
using namespace cv;

uchar SetBit(uchar value,int index)
{
	uchar mask = 1 << index;
	value &= mask;
	return value;
}

void Lmaskoperation(int* table, int* arr, int l)
{
	static int tmp[9] = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
	for (int i = 0; i < 9; i++)
	{
		table[l] = table[l] + tmp[i] * arr[i];
	}
}

void table_scale(int* table, uchar* result, int n)
{
	int min = table[0];
	int max = table[0];
	for (int i = 0; i < n; i++)
	{
		if (min > table[i])
		{
			min = table[i];
		}
		if (max < table[i])
		{
			max = table[i];
		}
	}
	for (int i = 0; i < n; i++)
	{
		result[i] = (uchar)(255 * (table[i] - min) / (max - min));
	}
}

int main(int argc, char *argv[])
{
	Mat src = imread("C:\\Users\\30974\\Desktop\\flower.jpg", 0);

	//get some informations of original image
	int nr = src.rows;
	int nc = src.cols;
	int n = nr * nc;
	int arr[9] = { 0 };

	//scan the whole pixels of original image 
	//and do Laplacian Operation
	int* table_lap = new int[n];
	int* table_orig = new int[n];
	int l;
	for (int i = 0; i < n; i++)
	{
		table_lap[i] = 0;
		table_orig[i] = 0;
	}
	for (int i = 1; i < nr - 1; i++)
	{
		const uchar* previous = src.ptr<uchar>(i - 1);
		const uchar* current = src.ptr<uchar>(i);
		const uchar* next = src.ptr<uchar>(i + 1);
		for (int j = 1; j < nc - 1; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				arr[k] = previous[j + k - 1];
				arr[k + 3] = current[j + k - 1];
				arr[k + 6] = next[j + k - 1];
			}
			l = nc * i + j;        //calculate the location in the table of current pixel
			Lmaskoperation(table_lap, arr, l);
			table_orig[l] = arr[4];
		}
	}

	//pixels scale
	uchar* La_scaled = new uchar[n];
	table_scale(table_lap, La_scaled, n);

	//padding values
	Mat LaResult_own;
	LaResult_own.create(src.size(), src.type());
	uchar* p = NULL;
	for (int i = 0; i < nr; i++)
	{
		p = LaResult_own.ptr<uchar>(i);
		for (int j = 0; j < nc; j++)
		{
			l = nc * i + j;
			p[j] = La_scaled[l];
		}
	}

	//show results
	//namedWindow("LaResult_own");
	//imshow("LaResult_own", LaResult_own);

	//blending with the original image using Eq g(x,y)=f(x,y)+c*Lap(x,y)
	int* table_blend = new int[n];
	for (int i = 0; i < n; i++)
	{
		table_blend[i] = table_orig[i] + table_lap[i];
		if (table_blend[i] < 0)
		{
			table_blend[i] = 0;
		}
		else if (table_blend[i] > 255)
		{
			table_blend[i] = 255;
		}
	}

	//padding values to blending result
	Mat Blresult;
	Blresult.create(src.size(), src.type());
	for (int i = 0; i < nr; i++)
	{
		p = Blresult.ptr<uchar>(i);
		for (int j = 0; j < nc; j++)
		{
			l = nc * i + j;
			p[j] = table_blend[l];
		}
	}

	//show blending result
	namedWindow("blending result_laplacian");
	imshow("blending result_laplacian", Blresult);
	
	//imshow("src", src);
	//Image img = CreateImage(src);

	//Laplace lp;
	//Image img_lp = lp(img);
	//
	////img_lp.calibrate();

	//Image res = img - img_lp;


	//res.calibrate();
	//Mat dst = GetMatFromImage(res);

	//imshow("dst", dst);

	waitKey();
	system("pause");
	return 0;
}