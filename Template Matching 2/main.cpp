#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
    matchTemplate to search for matches between an image patch and an input image
    How does template matching works?
    There must have to be two primary components
    Source Image (I) = The image in which we expect to find a match to the template image
    Template Image (T) = The patch image which will be compared to the template image
    The goal is to detect the highest matching area
    To identify the matching area, we have to compare the template image against the source image by sliding it
    By sliding, we mean moving the patch one pixel at a time (left to right, up to down).
    At each location, a metric is calculated so it represents how “good” or “bad” the match at that location is (or how similar the patch is to that particular area of the source image).
    For each location of T over I, you store the metric in the result matrix (R). Each location (x,y) in R contains the match metric:
    In practice, we use the function minMaxLoc to locate the highest value (or lower, depending of the type of matching method) in the R matrix.
    OpenCV implements Template matching in the function matchTemplate. The available methods are 6.
    CV_TM_SQDIFF, CV_TM_SQDIFF_NORMED, CV_TM_CCORR, CV_TM_CCORR_NORMED, CV_TM_CCOEFF, CV_TM_CCOEFF_NORMED
    The result of an image using the CV_CCORRR_NORMED results in the image where the brightest locations indicate the highest matches.
*/

int main()
{
    /*
    Mat image = imread("simpsons.jpg", CV_LOAD_IMAGE_COLOR);

    // Converting original image from RGB to GRAY
    Mat imageGray;
    cvtColor(image, imageGray, CV_BGR2GRAY);

    // Loading image template (GRAY)
    Mat templateImage = imread("barts_face.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    // Compare template against source image and store it into result Mat object
    Mat result;
    matchTemplate(imageGray, templateImage, result, CV_TM_CCOEFF_NORMED);

    // Find the brightest locations that indicate the highest matches in a vector of points (x,y).
    vector<Point>HighestMatch;
    for (int i = 0; i < result.rows; i++) {
        for(int j = 0; j < result.cols; j++) {
            if(result.at<float>(i,j) >= 0.9) {
                HighestMatch.push_back(Point(j,i)); // Saving locations
            }
        }
    }

    // Drawing rectangle in the original image
    for (int i = 0; i < (int)HighestMatch.size(); i++) {
        rectangle(image, HighestMatch[i], Point(HighestMatch[i].x + templateImage.cols, HighestMatch[i].y + templateImage.rows), Scalar(0,255,0), 2);
    }

    // showing images
    imshow("Image", image);
    imshow("Result", result);

    */

    VideoCapture cap(0);

    Mat frame;
    Mat templatePen = imread("pen.png",CV_LOAD_IMAGE_GRAYSCALE);

    while(true) {
        cap.read(frame);

        // Converting to gray
        Mat grayFrame;
        cvtColor(frame, grayFrame, CV_BGR2GRAY);

        // Compare template against source image and store it into result Mat object
        Mat result;
        matchTemplate(grayFrame, templatePen, result, CV_TM_CCOEFF_NORMED);

        // Find points where there are the highest match
        vector<Point> highestMatchPen;
        for(int i = 0; i < result.rows; i++) {
            for(int j = 0; j < result.cols; j++) {
                if(result.at<float>(i,j) >= 0.6) {
                    highestMatchPen.push_back(Point(j,i));
                }
            }
        }


        putText(frame, "Positioning here", Point(90, 80), FONT_HERSHEY_PLAIN, 2, Scalar(255, 0, 0), 2, LINE_AA);
        rectangle(frame, Point(90, 90), Point(350, 350), Scalar(0,0,255), 4);

        if(highestMatchPen.size() != 0) {
            putText(frame, "Blue Pen", Point(98, 380), FONT_HERSHEY_PLAIN, 2, Scalar(255, 0, 0), 2, LINE_AA);
        }

        // Showing frame
        imshow("Video", frame);

        if(waitKey(1) >= 0)
            break;
    }

    return 0;
}
