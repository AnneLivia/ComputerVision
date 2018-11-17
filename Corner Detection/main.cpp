#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

/*
    Corner Detection:
    Corner detection is an approach used within computer
    vision systems to extract certain kinds of features
    and infer the contents of an image. Corner detection
    is frequently used in motion detection, image
    registration, video tracking, image mosaicing,
    panorama stitching, 3D modelling and object
    recognition. Corner detection overlaps with the
    topic of interest point detection.

    A corner can be defined as the intersection of
    two edges. A corner can also be defined as a
    point for which there are two dominant and
    different edge directions in a local neighbourhood
    of the point.

    Function used here is: goodFeaturesToTrack, it Determines strong corners on an image.
    void goodFeaturesToTrack(InputArray image, OutputArray corners, int maxCorners, double qualityLevel, double minDistance, InputArray mask=noArray(), int blockSize=3, bool useHarrisDetector=false, double k=0.04 )


    image – Input 8-bit or floating-point 32-bit, single-channel image.
    eig_image – The parameter is ignored.
    temp_image – The parameter is ignored.
    corners – Output vector of detected corners.
    maxCorners – Maximum number of corners to return. If there are more corners than are found, the strongest of them is returned.
    qualityLevel – Parameter characterizing the minimal accepted quality of image corners. The parameter value is multiplied by the best corner quality measure, which is the minimal eigenvalue (see cornerMinEigenVal() ) or the Harris function response (see cornerHarris() ). The corners with the quality measure less than the product are rejected. For example, if the best corner has the quality measure = 1500, and the qualityLevel=0.01 , then all the corners with the quality measure less than 15 are rejected.
    minDistance – Minimum possible Euclidean distance between the returned corners.
    mask – Optional region of interest. If the image is not empty (it needs to have the type CV_8UC1 and the same size as image ), it specifies the region in which the corners are detected.
    blockSize – Size of an average block for computing a derivative covariation matrix over each pixel neighborhood. See cornerEigenValsAndVecs() .
    useHarrisDetector – Parameter indicating whether to use a Harris detector (see cornerHarris()) or cornerMinEigenVal().
    k – Free parameter of the Harris detector.

    The function finds the most prominent corners in the image or in the specified image region

*/

int main()
{
    Mat image = imread("image.jpg", CV_LOAD_IMAGE_COLOR);

    // Convert to gray, since, only can be used a single channel image, of either 8-bit or floating-point 32-bit
    Mat gray;
    cvtColor(image, gray, CV_BGR2GRAY);
    gray.convertTo(gray, CV_32F); // converting to 32 float bit

    vector<Point2f>corners; // Vector to store all the corners found
    goodFeaturesToTrack(gray, corners, 100, 0.01, 10, Mat()); // The parameters here are the image, max corners to detect, quality, and minimum distance between corners.

    for(auto corner : corners) {
        float x = corner.x;
        float y = corner.y;

        // Drawing circle with these two points
        circle(image, Point(x,y), 3, Scalar(0,255,255), -1); // Image, where the circle will be drawn, Point (location) in the grid, radius, color, if is a closed circle, or not.
    }

    imshow("Image", image);

    waitKey(0);
    return 0;
}
