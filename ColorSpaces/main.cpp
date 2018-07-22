#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat bright = imread("cubeLight.png",CV_LOAD_IMAGE_COLOR);
    Mat dark = imread("cubeLight.png", CV_LOAD_IMAGE_COLOR);

    Mat splitBright[3], splitDark[3];

    split(bright,splitBright);
    split(dark,splitDark);
/*
    imshow("Blue Bright",splitBright[0]);
    imshow("Green Bright",splitBright[1]);
    imshow("Red Bright",splitBright[2]);

    imshow("Blue Dark",splitDark[0]);
    imshow("Green Dark",splitDark[1]);
    imshow("Red Dark",splitDark[2]);

*/
    /*
        The rgb has the follow properties:
        It is an additive colorspace where colors are obtained by a linear combination of Red, Green, and Blue values.
        The three channels are correlated by the amount of light hitting the surface.

        Lab:
        The Lab color space has three components.

        L = Lightness ( Intensity ).
        a = color component ranging from Green to Magenta.
        b = color component ranging from Blue to Yellow.

        The Lab color space is quite different from the RGB color space. In RGB color space the color information is separated into three channels but the same three channels also encode brightness information. On the other hand, in Lab color space, the L channel is independent of color information and encodes brightness only. The other two channels encode color.

    */
    // converting rgb to lab
    Mat labBright, labDark;
    cvtColor(bright,labBright,COLOR_BGR2Lab);
    cvtColor(dark,labDark,COLOR_BGR2Lab);

    Mat labSplitBright[3], labSplitDark[3];
    split(labBright,labSplitBright);
    split(labDark,labSplitDark);
    /*
    imshow("LAB Lightness Bright",labSplitBright[0]);
    imshow("LAB Green to Magenta Bright",labSplitBright[1]);
    imshow("LAB Blue to Yellow Bright",labSplitBright[2]);

    imshow("LAB Lightness Dark",labSplitDark[0]);
    imshow("LAB Green to Magenta Dark",labSplitDark[1]);
    imshow("LAB Blue to Yellow Dark",labSplitDark[2]);
    */
    /*
        The YCrCb color space is derived from the RGB color space and has the following three compoenents.

        Y – Luminance or Luma component obtained from RGB after gamma correction.
        Cr = R – Y ( how far is the red component from Luma ).
        Cb = B – Y ( how far is the blue component from Luma ).

        This color space has the following properties.

        Separates the luminance and chrominance components into different channels.
        Mostly used in compression ( of Cr and Cb components ) for TV Transmission.
        Device dependent.
    */

    Mat brightYCB, darkYCB;
    cvtColor(bright,brightYCB,COLOR_BGR2YCrCb);
    cvtColor(dark,darkYCB,COLOR_BGR2YCrCb);

    Mat splitBrightYCB[3], splitDarkYCB[3];
    split(brightYCB,splitBrightYCB);
    split(darkYCB,splitDarkYCB);
    /*
    imshow("YCB Luma Bright",splitBrightYCB[0]);
    imshow("YCB Chroma Cr Bright",splitBrightYCB[1]);
    imshow("YCB Chroma Cb right",splitBrightYCB[2]);

    imshow("YCB Luma Dark",splitDarkYCB[0]);
    imshow("YCB Chroma Cr Dark",splitDarkYCB[1]);
    imshow("YCB Chroma Cb Dark",splitDarkYCB[2]);
    */

    /*
        The HSV color space has the following three components

        H – Hue ( Dominant Wavelength ).
        S – Saturation ( Purity / shades of the color ).
        V – Value ( Intensity ).

        Some of its properties.

        Best thing is that it uses only one channel to describe color (H),
        making it very intuitive to specify color.
        Device dependent.
    */

    Mat brightHSV, darkHSV;
    cvtColor(bright,brightHSV,COLOR_BGR2HSV);
    cvtColor(dark, darkHSV,COLOR_BGR2HSV);

    Mat splitBrightHSV[3], splitDarkHSV[3];

    split(brightHSV,splitBrightHSV);
    split(darkHSV,splitDarkHSV);

    imshow("HSV hue Bright",splitBrightHSV[0]);
    imshow("HSV Saturation Bright",splitBrightHSV[1]);
    imshow("HSV Value (intensity) right",splitBrightHSV[2]);

    imshow("HSV hue Dark",splitDarkHSV[0]);
    imshow("HSV Saturation Dark",splitDarkHSV[1]);
    imshow("HSV Value (intensity) Dark",splitDarkHSV[2]);
    waitKey(0);
    return 0;
}
