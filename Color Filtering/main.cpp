#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0); // Open the camera (0 - default)

    Mat frame;

    while(1) {
        cap.read(frame);
        Mat framehsv;

        /*
            HSV:
            Hue: Hue is the color portion of the color model, and is expressed as a number from 0 to 360 degrees
            Saturation: Saturation is the amount of gray in the color, from 0 to 100 percent. A faded effect can be had from reducing the saturation toward zero to introduce more gray.
            Value (brightness): Value works in conjunction with saturation and describes the brightness or intensity of the color, from 0-100 percent, where 0 is completely black and 100 is the brightest and reveals the most color.
        */

        // Converting to hsv
        cvtColor(frame,framehsv,CV_BGR2HSV);

        // Upper and lower Limits (hue, sat, val)
        Scalar lowerRed = Scalar(160,100,100);
        Scalar upperRed = Scalar(179,255,255);

        Mat imageMaskRed;

        // Getting the image mask (red)
        inRange(framehsv,lowerRed,upperRed,imageMaskRed);

        Mat result;

        // When there is one in the mask, will be shown the colors from the frame
        bitwise_and(frame, frame, result, imageMaskRed = imageMaskRed);

        imshow("Video", frame);
        imshow("Mask", imageMaskRed);
        imshow("Result", result);

        if(waitKey(1) >= 0)
            break;
    }
    return 0;
}
