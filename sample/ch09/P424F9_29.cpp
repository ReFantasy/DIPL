#include "dipl.h"
using namespace cv;
using namespace std;

bool IsSame(const Mat A, const Mat B)
{
    Mat dif = A - B;
    for (auto it = dif.begin<uchar>(); it != dif.end<uchar>(); it++)
    {
        if (*it != 0)
            return false;
    }

    return true;
}

// 9.5-22
Mat D_G(const Mat F, const Mat G, const Mat se, int n)
{
    Mat res;

    if (n == 0)
    {
        return F;
    }
    else if (n == 1)
    {

        dilate(F, res, se);
        bitwise_and(res, G, res);
        return res;
    }
    else
    {
        res = D_G(F, G, se, n - 1);
        return D_G(res, G, se, 1);
    }
}

// 9.5-24
Mat E_G(const Mat F, const Mat G, const Mat se, int n)
{
    Mat res;

    if (n == 0)
    {
        return F;
    }
    else if (n == 1)
    {

        erode(F, res, se);
        bitwise_or(res, G, res);
        return res;
    }
    else
    {
        res = E_G(F, G, se, n - 1);
        return E_G(res, G, se, 1);
    }
}

// 9.5-25
Mat RGD(const Mat F, const Mat G, const Mat se)
{
    Mat res_k_1 = F;
    Mat res_k = D_G(F, G, se, 1);

    while (!IsSame(res_k, res_k_1))
    {
        res_k_1 = res_k;
        res_k = D_G(res_k, G, se, 1);
    }

    return res_k;
}

Mat Open(const Mat src, const Mat se)
{
    Mat res;
    erode(src, res, se);
    dilate(res, res, se);
    return res;
}

int main(int argc, char *argv[])
{
    Mat src = imread(
        std::string(DATA_DIR) + "/DIP3E_Original_Images_CH09/Fig0929(a)(text_image).tif", 0);
    cv::threshold(src, src, 205, 255, THRESH_BINARY);

    Mat se = getStructuringElement(cv::MORPH_RECT, cv::Size(1, 51));

    Mat b;
    erode(src, b, se, {-1, -1}, 1);

    Mat c = Open(src, se);

    se = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    Mat d = RGD(c, src, se);

    imshow("a", src);
    imshow("b", b);
    imshow("c", c);
    imshow("d", d);

    waitKey();
    return 0;
}

// Mat B = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
// Mat F(9, 10, CV_8UC1, Scalar(0));
// for (int i = 1; i <= 4; i++)
//{
//	for (int j = 1; j <= 6; j++)
//	{
//		F.at<uchar>(i, j) = 255;
//	}
// }
// F.at<uchar>(1, 6) = 255;
// F.at<uchar>(4, 1) = 255;
// F.at<uchar>(4, 2) = 255;
//
// Mat G(9, 10, CV_8UC1, Scalar(0));
// G.at<uchar>(2, 2) = 255;
// G.at<uchar>(3, 2) = 255;
// G.at<uchar>(3, 3) = 255;
// G.at<uchar>(4, 3) = 255;
// for (int i = 5; i <= 7; i++)
//{
//	for (int j = 3; j <= 5; j++)
//	{
//		G.at<uchar>(i, j) = 255;
//	}
// }
// G.at<uchar>(6, 4) = 0;
//
// Mat res = EGF(F, G, B, 30);
// resize(res, res, { 100,90 });
// imshow("res", res);
