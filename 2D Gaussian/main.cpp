#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Size is how big the mat will be
// Control how the gaussian is create, mean, sigmal, x and y
void createGaussian(Size si, Mat& output, int uX, int uY, float sigmaX, float sigmaY, float amplitude = 1.0f) {
    Mat temp = Mat(si,CV_32F); // temporary mat to store information
    // Equation for gaussian function is:
    for ( int r = 0; r < si.height; r++) {
        for ( int c = 0; c < si.width; c++) {
            float x = ((c-uX)*((float)c-uX)) / (2.0f * sigmaX * sigmaX);
            float y = ((r-uY)*((float)r-uY)) / (2.0f * sigmaY * sigmaY);
            float value = amplitude * exp(-(x + y));
            temp.at<float>(r,c) = value;
        }
    }
    normalize(temp,temp,0.0f,1.0f,NORM_MINMAX);

    output = temp;
}

int main()
{
    Mat output;
    createGaussian(Size(256,256), output, 256/2, 256/2,10,10);
    imshow("Gaussian",output);
    waitKey();
    return 0;
}
