#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat img1 = imread("im1.png", CV_LOAD_IMAGE_COLOR);
    Mat img2 = imread("im2.png", CV_LOAD_IMAGE_COLOR);

    Mat andBitwiseIm, xorBitwiseIm, orBitwiseIm, notBitwiseIm1, notBitwiseIm2;

    // Bitwise and (0 and 0 = 0, 0 and 1 = 0, 1 and 0 = 0, 1 and 1 = 1)
    bitwise_and(img1, img2, andBitwiseIm);

    // Bitwise or (0 and 0 = 0, 0 and 1 = 1, 1 and 0 = 1, 1 and 1 = 1)
    bitwise_or(img1, img2, orBitwiseIm);

    // Bitwise XOR (0 and 0 = 0, 0 and 1 = 1, 1 and 0 = 1, 1 and 1 = 0)
    bitwise_xor(img1, img2, xorBitwiseIm);

    // Bitwise not (1 = 0, 0 = 1)
    bitwise_not(img1, notBitwiseIm1);
    bitwise_not(img2, notBitwiseIm2);

    imshow("Image 1", img1);
    imshow("Image 2", img2);

    imshow("Bitwise And", andBitwiseIm);
    imshow("Bitwise Or", orBitwiseIm);
    imshow("Bitwise Xor", xorBitwiseIm);
    imshow("Bitwise Not 1", notBitwiseIm1);
    imshow("Bitwise Not 2", notBitwiseIm2);

    waitKey();

    return 0;
}
