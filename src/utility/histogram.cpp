#include "utility/histogram.h"
#include <vector>
#include <matplot/matplot.h>

// https://blog.csdn.net/qq_37764129/article/details/81871745
Mat GetHistogram(const Mat grayImage)
{
    // // 定义求直方图的通道数目，从0开始索引
    // int channels[] = {0};
    //
    // // 定义直方图的在每一维上的大小，例如灰度图直方图的横坐标是图像的灰度值，就一维，bin的个数
    // // 如果直方图图像横坐标bin个数为x，纵坐标bin个数为y，则channels[]={1,2}其直方图应该为三维的，Z轴是每个bin上统计的数目
    // const int histSize[] = {256};
    //
    // // 每一维bin的变化范围
    // float range[] = {0, 256};
    //
    // // 所有bin的变化范围，个数跟channels应该跟channels一致
    // const float* ranges[] = {range};
    //
    // // 定义直方图，这里求的是直方图数据
    // Mat hist;
    //
    // // opencv中计算直方图的函数，hist大小为256*1，每行存储的统计的该行对应的灰度值的个数
    // calcHist(&grayImage, 1, channels, Mat(), hist, 1, histSize, ranges, true,
    //          false); // cv中是cvCalcHist
    //
    // // 找出直方图统计的个数的最大值，用来作为直方图纵坐标的高
    // double maxValue = 0;
    // // 找矩阵中最大最小值及对应索引的函数
    // minMaxLoc(hist, 0, &maxValue, 0, 0);
    // // 最大值取整
    // int rows = cvRound(maxValue);
    //
    // // 定义直方图图像，直方图纵坐标的高作为行数，列数为256(灰度值的个数)
    // // 因为是直方图的图像，所以以黑白两色为区分，白色为直方图的图像
    // Mat histImage = Mat::zeros(rows, 256, CV_8UC1);
    //
    // // 直方图图像表示
    // for (int i = 0; i < 256; i++)
    // {
    //     // 取每个bin的数目
    //     int temp = (int)(hist.at<float>(i, 0));
    //
    //     // 如果bin数目为0，则说明图像上没有该灰度值，则整列为黑色
    //     // 如果图像上有该灰度值，则将该列对应个数的像素设为白色
    //     if (temp)
    //     {
    //         // 由于图像坐标是以左上角为原点，所以要进行变换，使直方图图像以左下角为坐标原点
    //         histImage.col(i).rowRange(Range(rows - temp, rows)) = 255;
    //     }
    // }
    //
    // // 由于直方图图像列高可能很高，因此进行图像对列要进行对应的缩减，使直方图图像更直观
    // Mat resizeImage;
    // resize(histImage, resizeImage, Size(256, 256));
    //
    // return resizeImage;


    // 1. 加载图像
    // Mat src = imread("lena.jpg", IMREAD_GRAYSCALE); // 以灰度模式加载
    // if (src.empty()) {
    //     cout << "无法加载图像!" << endl;
    //     return -1;
    // }
    cv::Mat src = grayImage;

    // 2. 设置直方图参数
    Mat hist; // 用于存储直方图结果
    int histSize[] = { 256 }; // Bin的数量 (0-255，共256个)

    // 像素值范围 (对于8位图像是0-255)
    // 注意：上限是不包含的，所以是256
    float hranges[] = { 0.0f, 256.0f };
    const float* ranges[] = { hranges };

    int channels[] = { 0 }; // 我们只处理灰度图的第0个通道

    // 3. 计算直方图
    calcHist(&src,      // 输入图像 (注意是地址)
             1,          // 图像数量
             channels,   // 通道列表
             Mat(),      // 无掩码
             hist,       // 输出直方图
             1,          // 直方图维度 (1D)
             histSize,   // 每个维度的bin数量
             ranges      // 每个维度的取值范围
    );
    //std::cout << hist.size() << std::endl;
    std::cout << hist << std::endl;

    // (可选) 打印一些直方图的值（hist现在是一个256x1的Mat）
    // for (int i = 0; i < histSize[0]; i++) {
    //     cout << "灰度值 " << i << ": " << hist.at<float>(i, 0) << " 个像素" << endl;
    // }

    // 4. (重要!) 可视化直方图
    // `calcHist` 计算出来的是数值，我们还需要把它画出来才能直观看到。
    int hist_w = 512; // 直方图图像的宽度
    int hist_h = 400; // 直方图图像的高度
    int bin_w = cvRound((double)hist_w / histSize[0]); // 每个bin在图像中的宽度

    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(20, 20, 20)); // 创建一个黑色背景的图像用于绘制

    // 归一化直方图的值到 [0, hist_h] 区间，这样才能画在图上
    // `normalize` 函数会找到hist中的最大值，然后按比例缩放所有值
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    // 绘制直方图的每个bin
    for (int i = 1; i < histSize[0]; i++) {
        line(histImage,
             Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))), // 上一个点
             Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),     // 当前点
             Scalar(200, 200, 200), // 线条颜色 (浅灰色)
             2, 8, 0);
    }

    // 5. 显示原图和直方图
    //imshow("Src Image", src);
    //imshow("Histogram Image", histImage);
    return histImage;
}


std::vector<int> ComputeHistogram(const cv::Mat& gray_image, bool show)
{
    std::vector<int> hist(256, 0);
    const unsigned char* pdata = gray_image.data;

    // for (int i=0; i<gray_image.rows*gray_image.cols; i++)
    //     hist[static_cast<int>(pdata[i])]++;

#pragma omp parallel for
    for (int r = 0; r < gray_image.rows; ++r)
    {
        const auto* row = gray_image.ptr<uchar>(r);
        for (int c = 0; c < gray_image.cols; ++c)
#pragma omp atomic
            ++hist[row[c]];
    }

    if (show)
    {
        // 构造横坐标 0..255
        std::vector<double> x(256);
        std::iota(x.begin(), x.end(), 0.0);

        // 转成 double（bar 接受 vector<double>）
        std::vector<double> y(hist.begin(), hist.end());

        auto bar = matplot::bar(x, y);
        bar->face_color("steelblue");
        bar->line_width(1);

        matplot::title("Grayscale Histogram");
        matplot::xlabel("Gray level");
        matplot::ylabel("Count");
        //matplot::show();
        matplot::save("hist.jpg");
    }


    return hist;
}
