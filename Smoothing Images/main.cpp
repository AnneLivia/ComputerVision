#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
    Smoothing is also called blurring, which is a simple image processing operation.
    There are many reasons for smoothing, such as reduce noise.
    To perform a smoothing operation, will be used a filter to the image, the most commom
    type of filter are linear, in which an output pixel's value is determined as a weighted
    sum of input pixel values.
    g(i,j) = sum f(i + k, j + l)h(k,l);
    where h(k,l) is called the kernel which is nothing more than the coefficients of the filter
    it helps to visualize a filter as a window of coefficients sliding across the image

    As in one-dimensional signals, images also can be filtered with various low-pass filters(LPF), high-pass filters(HPF) etc. LPF helps in removing noises, blurring the images etc. HPF filters helps in finding edges in the images.

*/
int main()
{
    Mat image = imread("horse1.jpg",CV_LOAD_IMAGE_COLOR);
    Mat burImage;
    blur(image,burImage,Size(5,5));
    cvNamedWindow("Horse",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Blur Image",CV_WINDOW_AUTOSIZE);
    imshow("Horse",image);
    imshow("Blur Image",burImage);
    // Continue

    waitKey();
    return 0;
}
