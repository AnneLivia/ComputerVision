#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
    Font: https://homepages.inf.ed.ac.uk/rbf/HIPR2/affine.htm
    In many imaging systems, detected images are subject to geometric distortion introduced by perspective irregularities
    wherein the position of the camera(s) with respect to the scene alters the apparent dimensions of the scene geometry.
    Applying an affine transformation to a uniformly distorted image can correct for a range of perspective distortions by
    transforming the measurements from the ideal coordinates to those actually used. (For example, this is useful in satellite
    imaging where geometrically correct ground maps are desired.)
*/

int main()
{
    Mat image = imread("grid.jpg", CV_LOAD_IMAGE_COLOR);

    // Draw points in the image
    circle(image,Point(83, 90), 5, Scalar(0,255,0), - 1);
    circle(image,Point(447, 90), 5, Scalar(0,255,0), - 1);
    circle(image,Point(83, 472), 5, Scalar(0,255,0), - 1);

    // Points
    vector<Point2f>points = {
        Point(83, 90), Point(447, 90), Point(83, 472)
    };

    // Size image
    vector<Point2f> sizeImage = {Point(0,0), Point(447, 90), Point(150, 472)};

    Mat matrix, result;
    matrix = getAffineTransform(points, sizeImage);
    warpAffine(image, result, matrix, Size(image.cols, image.rows));

    imshow("Image", image);
    imshow("Result", result);
    waitKey(0);
    return 0;
}
