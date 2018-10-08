#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat image = imread("imagebook.jpg",CV_LOAD_IMAGE_COLOR);

    Mat thresholdImage1, thresholdImage2;

    // anything bellow 12 will be black, greater will be white
    threshold(image,thresholdImage1,12,255,CV_THRESH_BINARY);

    imshow("Original Image", image);



    Mat gray;

    cvtColor(image,gray,CV_BGR2GRAY);

    threshold(gray,thresholdImage2,12,255,CV_THRESH_BINARY);

    imshow("Threshold 1", thresholdImage1);
    imshow("Threshold 2", thresholdImage2);

    // Adaptive threshold

    Mat gaussian_adaptive_thresh;
    adaptiveThreshold(gray,gaussian_adaptive_thresh,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 115, 1);

    imshow("Gaussian Adaptive Thresh", gaussian_adaptive_thresh);
    waitKey();
    return 0;
}
