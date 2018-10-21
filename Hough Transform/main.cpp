#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
    What is hough transform?
    The Hough transform is a technique which can be used to isolate features
    of a particular shape within an image. Because it requires that the desired
    features be specified in some parametric form, the classical Hough transform
    is most commonly used for the detection of regular curves such as lines, circles, ellipses, etc.

    In OpenCV there are two implementation of hough transform, the standard one (HoughLines) and the
    probabilistic hough line transform which is more efficient (HoughLinesP);

    Explanation taken from: https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_lines/hough_lines.html
*/

int main()
{
    /*
    // Loading images
    Mat image = imread("lines.png");

    // Detect line using hough transform

    /*
        // This one is heavy
        HoughLines(): Finds lines in a binary image using the standard Hough transform.
        void HoughLines(InputArray image, OutputArray lines, double rho, double theta, int threshold, double srn=0, double stn=0 )
        Parameters:
            image = 8-bit, single-channel binary source image. The image may be modified by the function.
            lines = Output vector of lines. Each line is represented by a two-element vector (\rho, \theta) .
                    \rho is the distance from the coordinate origin (0,0) (top-left corner of the image).
                    \theta is the line rotation angle in radians ( 0 ~ {vertical line}, pi/2 ~ {horizontal line} ).
            rho = Distance resolution of the accumulator in pixels.
            theta = Angle resolution of the accumulator in radians.
            threshold = Accumulator threshold parameter. Only those lines are returned that get enough votes ( > {threshold} ).
            srn = For the multi-scale Hough transform, it is a divisor for the distance resolution rho .
                  The coarse accumulator distance resolution is rho and the accurate accumulator resolution is
                  rho/srn. If both srn=0 and stn=0 , the classical Hough transform is used.
                  Otherwise, both these parameters should be positive.
            stn = For the multi-scale Hough transform, it is a divisor for the distance resolution theta.
            method = One of the following Hough transform variants:
                    CV_HOUGH_STANDARD, CV_HOUGH_PROBABILISTIC, CV_HOUGH_MULTI_SCALE
            ....
            Better explanation: http://homepages.inf.ed.ac.uk/rbf/HIPR2/hough.htm

        HoughLinesP(): Finds line segments in a binary image using the probabilistic Hough transform.
        void HoughLinesP(InputArray image, OutputArray lines, double rho, double theta, int threshold, double minLineLength=0, double maxLineGap=0 )
        Parameters:
            image = 8-bit, single-channel binary source image. The image may be modified by the function.
            lines = Output vector of lines. Each line is represented by a 4-element vector (x_1, y_1, x_2, y_2) , where (x_1,y_1) and (x_2, y_2) are the ending points of each detected line segment.
            rho = Distance resolution of the accumulator in pixels.
            theta = Angle resolution of the accumulator in radians.
            threshold = Accumulator threshold parameter. Only those lines are returned that get enough votes ( > {threshold} ).
            minLineLength = Minimum line length. Line segments shorter than that are rejected.
            maxLineGap = Maximum allowed gap between points on the same line to link them.

    */ /*

    // Converting image to gray in order to detect edges
    Mat gray;
    cvtColor(image, gray, CV_BGR2GRAY);

    // Getting the edge of the image in order to use hough line
    Mat edges;
    Canny(gray, edges, 75, 100); // Parameters being used here are: input image, output image, lower threshold and upper threshold

    // Detecting the lines using hough line P
    vector<Vec4i> lines; // The function returns 4 points
    HoughLinesP(edges, lines, 1, CV_PI/180, 50, 0, 250);

    // Drawing the lines
    for (int i = 0; i < (int)lines.size(); i++) {
        Vec4i l = lines[i]; // Getting the points
        line(image, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,255,0), 2, LINE_AA);
    }

    // Showing images
    imshow("Edges", edges);
    imshow("Image", image);

    waitKey(0);
    */

    // Loading a video taken from: https://pysource.com/wp-content/uploads/2018/03/road_car_view.mp4
    // To ways to load a video
    // VideoCapture video("street.mp4");
    VideoCapture video = VideoCapture("street.mp4");

    // Showing video
    while(true) {
        Mat frame; // Mat to store frame
        if(!video.read(frame)) // Storing frames from the video in the frame Mat
            VideoCapture video("street.mp4"); // If the video finishes, the video will be loaded again

        // Converting frame from RGB to HSV to get the yellow lines
        Mat hsv;
        cvtColor(frame, hsv, CV_BGR2HSV);

        // Applying some enhancement like Gaussian blur
        GaussianBlur(hsv, hsv, Size(5,5), 1.4);

        // Applying range (lower and upper) yellow
        Scalar lowerb = Scalar(18, 94, 140);
        Scalar upperb = Scalar(48, 255, 255);
        Mat mask;
        inRange(hsv, lowerb, upperb, mask);

        // Applying canny edge detector
        Mat edges;
        Canny(mask, edges, 75, 150);

        // Using hough transform to detect street lines
        vector<Vec4i> lines; // vector to store the lines
        HoughLinesP(edges, lines, 1, CV_PI/180, 80, 0, 50);

        if(!lines.empty()) {
            // Drawing line in the original frame
            for (int i = 0; i < (int)lines.size(); i++) {
                Vec4i l = lines[i]; // Getting the line points
                line(frame, Point(l[0], l[1]), Point(l[2],l[3]), Scalar(0,255,0), 2, LINE_AA); // Drawing lines
            }
        }

        imshow("Frame", frame);

        if(waitKey(1) >= 0) // If any key is pressed, break.
            break;
    }

    return 0;
}
