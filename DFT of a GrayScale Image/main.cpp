#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void takeDFT(Mat& source, Mat& destination) {
    /*
        The Fourier Transform will decompose an image into its sinus and cosines components.
        In other words, it will transform an image from its spatial domain to its frequency domain. The idea is that any function may be approximated exactly with the sum of infinite sinus and cosines functions. The Fourier Transform is a way how to do this. Mathematically a two dimensional images Fourier transform is:
    */

    // real and imaginary components
    Mat originalComplex[2] = {source, Mat::zeros(source.size(),CV_32F)};

    Mat dftReady;

    merge(originalComplex,2, dftReady);

    dft(dftReady,destination, DFT_COMPLEX_OUTPUT);
}

void recenterDFT(Mat& source) {
    int centerX = source.cols/2;
    int centerY = source.rows/2;
    // rect draws a rectangle
    Mat q1(source,Rect(0,0,centerX,centerY));
    Mat q2(source,Rect(centerX,0,centerX,centerY));
    Mat q3(source,Rect(0,centerY,centerX,centerY));
    Mat q4(source,Rect(centerX,centerY,centerX,centerY));

    Mat swapMap;

    q1.copyTo(swapMap);
    q4.copyTo(q1);
    swapMap.copyTo(q4);

    q2.copyTo(swapMap);
    q3.copyTo(q2);
    swapMap.copyTo(q3);
}

// moving back from frequency domain to spacial domain

void invertDFT(Mat& source, Mat& destination) {
    Mat inverse;

    dft(source,inverse,DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

    destination = inverse;
}

void showDFT(Mat& source) {
    // Split the channels real and imaginary channels
    Mat splitarray[2] = {Mat::zeros(source.size(),CV_32F), Mat::zeros(source.size(),CV_32F)};

    split(source,splitarray); // Put each channel in splitarray

    // Take magnitude

    Mat dftMagnitude;

    magnitude(splitarray[0],splitarray[1],dftMagnitude);

    // The values are in normal range, they must be in log form

    dftMagnitude += Scalar::all(1); // add 1 in every single element in the objetct

    log(dftMagnitude,dftMagnitude);

    // Normalize

    normalize(dftMagnitude,dftMagnitude, 0, 1, CV_MINMAX);

    // recenter DFT, so the low frequency information is in the center and the high is in the conner instead
    // this is done just for visualization

    recenterDFT(dftMagnitude);

    imshow("DFT",dftMagnitude);

    waitKey();

}



int main()
{
    Mat original = imread("Horse1.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    // to take the dft, the image must be in gray scale
    // If ones want to take the dft of a color image, the image must be split into the channels

    // We need to use a float value of the image

    Mat originalFloat;

    original.convertTo(originalFloat, CV_32F, 1.0 / 255.0); // converting the image to float
    // the 1.0 / 255.0 is to tell that the numbers will range from 1 to 0, and they are being divided by 255 because the must be normalized

    Mat dftOfOriginal;

    takeDFT(originalFloat, dftOfOriginal);


    // Visualizing the dft
    showDFT(dftOfOriginal);

    Mat invertedDft;

    invertDFT(dftOfOriginal, invertedDft);

    imshow("InvertDFT result", invertedDft);

    waitKey();
    return 0;
}
