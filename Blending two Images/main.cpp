#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
    What is linear blending? is a dyadic (two-input) operator
    function: g(x) = (1 - alpha)F0(x) + alpha * f1(x);
    By varying alpha from 0 to 1, this operator can be used to perform a temporal cross-dissolve
    between two image or videos, as seen in slide shows and film productions.
*/

int main()
{
    double alpha = 0.5;
    double beta;
    double input;

    // Image 1 for f0(X) and image 2 for f1(x), since its an addition, both src1 and src2 must be of the same size (height and weight) and type
    Mat src1 = imread("canadaflag.jpg",CV_LOAD_IMAGE_COLOR);
    Mat src2 = imread("square.jpg",CV_LOAD_IMAGE_COLOR);

    if(!src1.data || !src2.data) {
        cout << "Error in images\n";
        return -1;
    }

    Mat dst;
    cout << "Type the alpha level, from 0 to 1: ";
    cin >> input;
    if(input >= 0.0 && input <= 1.0)
        alpha = input;

    namedWindow("Blending",CV_WINDOW_AUTOSIZE);

    beta = (1.0 - alpha);

    /*
        void addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst, int dtype=-1);
        parameters:

        src1 - first input array.
        alpha - weight of the first array elements.
        src2 - second input array of the same size and channel number as src1.
        beta - weight of the second array elements.
        dst - output array that has the same size and number of channels as the input arrays.
        gamma - scalar added to each sum.
        dtype - optional depth of the output array; when both input arrays have the same depth, dtype can be set to -1, which will be equivalent to src1.depth().

        Calculates the weighted sum of two arrays.

        Formula used: dst(i) = saturate(src1(I) * alpha + src2(I) * beta + gamma) where I is a multi-dimensional index of array elements.
        In case of multi-channel arrays, each channel is processed independently.
        The function can be replaced with a matrix expression:
        dst = src1*alpha + src2*beta + gamma;
    */
    addWeighted(src1, alpha, src2, beta, 0.0, dst);

    imshow("Blending",dst);

    waitKey();

    return 0;
}
