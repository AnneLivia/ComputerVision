#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0);

    Mat frame, image1, image2, mask1, mask2;

    /*
    image1 = imread("orange.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    image2 = imread("balls.jpg", CV_LOAD_IMAGE_GRAYSCALE);


    threshold(image1, mask1, 230, 255, CV_THRESH_BINARY_INV);
    threshold(image2, mask2, 250, 255, CV_THRESH_BINARY_INV);

    // Creating Kernel, the bigger the kernel the greater is going to be the dilation, erosion, etc.
    Mat kernel;
    Mat::ones(5,5,CV_8UC1);

    // Fill the holes
    Mat dilation;
    dilate(mask1, dilation, kernel);

    // Separate objects
    Mat erosion;

    // Iterate more than one time
    erode(mask2, erosion, kernel, Point(), 6);

    imshow("Erosion", erosion);
    imshow("Image", image2);
    imshow("Mask", mask2);

    */

    // Creating trackbars to get proper color to create a mask
    namedWindow("Trackbar", CV_WINDOW_NORMAL);

    // First is the name of the trackbar, then is the name of the window that this is going to be applied, the are the value range from one to another

    // Lower bound
    createTrackbar("LOWER - H", "Trackbar", 0, 179);
    createTrackbar("LOWER - S", "Trackbar", 0, 255);
    createTrackbar("LOWER - V", "Trackbar", 0, 255);

    // Upper bound
    createTrackbar("UPPER - H", "Trackbar", 0, 179);
    createTrackbar("UPPER - S", "Trackbar", 0, 255);
    createTrackbar("UPPER - V", "Trackbar", 0, 255);

    while(true) {
        cap.read(frame);
        Mat hsv; // Mat object to receive image in hsv format

        // converting image from rgb to hsv
        cvtColor(frame, hsv, CV_BGR2HSV);

        // Getting the value from window
        int lower_h = getTrackbarPos("LOWER - H", "Trackbar");
        int lower_s = getTrackbarPos("LOWER - S", "Trackbar");
        int lower_v = getTrackbarPos("LOWER - V", "Trackbar");
        int upper_h = getTrackbarPos("UPPER - H", "Trackbar");
        int upper_s = getTrackbarPos("UPPER - S", "Trackbar");
        int upper_v = getTrackbarPos("UPPER - V", "Trackbar");

        // Creating scalar color with those values
        Scalar lowerb = Scalar(lower_h, lower_s, lower_v);
        Scalar upperb = Scalar(upper_h, upper_s, upper_v);

        // Creating the mask with range function
        Mat mask;
        inRange(hsv, lowerb, upperb, mask);

        // Kernel to apply morphology operations
        Mat kernel = Mat::ones(5,5, CV_8U);

        // Applying erosion to the mask
        Mat erosion;
        erode(mask, erosion, kernel);


        // Dilation image
        Mat dilation;
        dilate(mask, dilation, kernel);

        // Deleting the image applying the bitwise and
        Mat result;
        bitwise_and(frame, frame, result, mask = mask);

        imshow("Result", result);
        imshow("Frame", frame);
        imshow("Mask", mask);
        imshow("Erosion", erosion);
        imshow("Dilation", dilation);




        if(waitKey(1) >= 0)
            break;
    }


    // waitKey();

    return 0;
}
