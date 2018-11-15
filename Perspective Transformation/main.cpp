#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
    When human eyes see near things they look bigger as compare to those who are far away. This is called perspective in a general way. Whereas transformation is the transfer of an object e.t.c from one state to another.
    So overall, the perspective transformation deals with the conversion of 3d world into 2d image. The same principle on which human vision works and the same principle on which the camera works.
*/
int main()
{

    Mat frame = imread("paper.png",CV_LOAD_IMAGE_COLOR);

    int height = frame.rows;
    int width = frame.cols;

    // Define some points, top left, top right, bottom left and right for the paper
    circle(frame, Point(width - 269,height - 224), 5, Scalar(0,0,255), -1);
    circle(frame, Point(width - 38, height - 219), 5, Scalar(0,0,255), -1);
    circle(frame, Point(width - 300,height - 54), 5, Scalar(0,0,255), -1);
    circle(frame, Point(width - 10, height - 52), 5, Scalar(0,0,255), -1);

    vector<Point2f>points = {
        Point(width - 269,height - 224), // Top left
        Point(width - 38, height - 219), // Top right
        Point(width - 300,height - 54),  // Bottom left
        Point(width - 10, height - 52)   // Bottom right
    };

    line(frame, points[0],points[1], Scalar(0,255,0), 2, LINE_AA);
    line(frame, points[0],points[2], Scalar(0,255,0), 2, LINE_AA);
    line(frame, points[1],points[3], Scalar(0,255,0), 2, LINE_AA);
    line(frame, points[2],points[3], Scalar(0,255,0), 2, LINE_AA);

    vector<Point2f> sizeImage = {Point(0,0), Point(width - 1, 0), Point(0, height - 1), Point(width - 1, height - 1)};

    Mat matrix, result;

    matrix = getPerspectiveTransform(points, sizeImage);

    warpPerspective(frame, result, matrix, result.size());

    imshow("Frame", frame);
    imshow("Result", result);

    waitKey();

    return 0;
}
