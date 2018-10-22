#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat image = imread("white_panda.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    // to remove noise, will be applied to the image a Gaussian blur
    GaussianBlur(image, image, Size(5,5), 0);

    // Sobel find the change of intensity horizontally and vertically
    Mat sobelx, sobely, sobelxAndy;

    Sobel(image, sobelx, CV_64F, 1, 0); // Horizontally
    Sobel(image, sobely, CV_64F, 0, 1); // Vertically
    Sobel(image, sobelxAndy, CV_64F, 1, 1); // Both

    // Laplacian
    Mat lapla;
    Laplacian(image, lapla, CV_64F, 11);

    // Canny
    Mat canny;
    Canny(image, canny, 100, 150);
    imshow("Image", image);
    imshow("Sobel x", sobelx);
    imshow("Sobel y", sobely);
    imshow("Sobel x and y", sobelxAndy);
    imshow("Canny", canny);
    imshow("Laplacian", lapla);

    waitKey();
    return 0;
}
