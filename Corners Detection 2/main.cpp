#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
    Corner detection is an approach used within computer vision
    systems to extract certain kinds of features and infer the
    contents of an image. Corner detection is frequently used in
    motion detection, image registration, video tracking,
    image mosaicing, panorama stitching, 3D modelling and object recognition.

    corners are regions in the image with large variation in intensity in all the directions
    OpenCV has the function cv2.cornerHarris() for this purpose. Its arguments are :
        img - Input image, it should be grayscale and float32 type.
        blockSize - It is the size of neighbourhood considered for corner detection
        ksize - Aperture parameter of Sobel derivative used.
        k - Harris detector free parameter in the equation.

    continue...
*/

int main()
{
    Mat image = imread("squares.jpg", CV_LOAD_IMAGE_COLOR);

    // Converting the image to gray
    Mat gray;
    cvtColor(image, gray, CV_BGR2GRAY);

    // Detecting corners

    imshow("Image", image);
    waitKey(0);
    return 0;
}
