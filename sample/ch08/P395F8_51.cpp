#include "dipl.h"
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{

    Mat src = imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH08/Fig0809(a).tif", 0);
    Mat logo = imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH08/Fig0850(a).tif", 0);

    // 将图像的最低两位置零
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            src.data[i * src.cols + j] &= 0XFC;
        }
    }

    // 将logo最高两位移动到最低两位
    for (int i = 0; i < logo.rows; i++)
    {
        for (int j = 0; j < logo.cols; j++)
        {
            logo.data[i * logo.cols + j] >>= 6;
        }
    }

    // 将logo 写入图像中间位置
    int in_row = 400;
    int in_col = 100;
    for (int i = 0; i < logo.rows; i++)
    {
        for (int j = 0; j < logo.cols; j++)
        {
            src.data[(i + in_row) * src.cols + (j + in_col)] += logo.data[i * logo.cols + j];
        }
    }

    // 提取水印
    // 将图像的最低两位置零
    Mat logo_built(src.rows, src.cols, CV_8UC1, Scalar(0));
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            logo_built.data[i * src.cols + j] = src.data[i * src.cols + j] & 0X3;
        }
    }
    cv::equalizeHist(logo_built, logo_built);

    Mat src_to_jpg;
    imwrite("tmp.jpeg", src);
    src_to_jpg = imread("tmp.jpeg", 0);

    Mat logo_built2(src_to_jpg.rows, src_to_jpg.cols, CV_8UC1, Scalar(0));
    for (int i = 0; i < src_to_jpg.rows; i++)
    {
        for (int j = 0; j < src_to_jpg.cols; j++)
        {
            logo_built2.data[i * src_to_jpg.cols + j] =
                src_to_jpg.data[i * src_to_jpg.cols + j] & 0X3;
        }
    }
    cv::equalizeHist(logo_built2, logo_built2);

    imshow("a", src);
    imshow("b", logo_built);
    imshow("c", src_to_jpg);
    imshow("d", logo_built2);

    waitKey();
    return 0;
}
