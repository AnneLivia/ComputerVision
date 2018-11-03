#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

/*
    What is template matching:
    Template matching is a technique for finding areas of an image that match (are similar)
    to a template image (patch). While the patch must be a rectangle it may be that not all
    of the rectangle is relevant. In such a case, a mask can be used to isolate the portion
    of the patch that should be used to find the match.

    How it works?
    We need two primary components:
    Source image: The image in which we expect to find a match to the template image
    Template Image: The patch image which will be compared to the template image

    To identify the matching area, we have to compare the template image against the source image by sliding it
    By sliding, we mean moving the patch one pixel at a time (left to right, up to down). At each location, a
    metric is calculated so it represents how "good" or "bad" the match at that location is (or how similar
    the patch is to that particular area of the source image).

*/

int main()
{
    // Loading the source image
    Mat image_bgr = imread("main_image.jpg", CV_LOAD_IMAGE_COLOR);

    // converting to gray
    Mat image_gray;
    cvtColor(image_bgr, image_gray, CV_BGR2GRAY);

    // loading the image template
    Mat template_image = imread("template.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    // Getting size of the template image, height and width
    int width_template, height_template;
    width_template = template_image.cols;
    height_template = template_image.rows;

    /* MatchTemplate is the function used to find areas of an image that match (are similar) to a template image (patch).

        void cv::matchTemplate (InputArray image, InputArray templ, OutputArray result, int method, InputArray mask = noArray())

        image – Image where the search is running. It must be 8-bit or 32-bit floating-point.
        templ – Searched template. It must be not greater than the source image and have the same data type.
        result – Map of comparison results. It must be single-channel 32-bit floating-point. If image is W \times H and templ is w \times h , then result is (W-w+1) \times (H-h+1) .
        method – Parameter specifying the comparison method (see below).

        method=CV_TM_SQDIFF
        CV_TM_SQDIFF - Sum of Square Differences (or SSD):
            Simple euclidian distance (squared):
                Take every pair of pixels and subtract
                Square the difference
                Sum all the squares

        method=CV_TM_SQDIFF_NORMED
        CV_TM_SQDIFF_NORMED - SSD Normed
            This is rarely used in practice, but the normalization part is similar in the next methods.
            The nominator term is same as above, but divided by a factor, computed from the - square root of the product of:
                sum of the template, squared
                sum of the image window, squared

        method=CV_TM_CCORR
        CV_TM_CCORR - Cross Correlation
        Basically, this is a dot product:
            Take every pair of pixels and multiply
            Sum all products

        method=CV_TM_CCORR_NORMED

        method=CV_TM_CCOEFF
        Similar to Cross Correlation, but normalized with their Covariances

        method=CV_TM_CCOEFF_NORMED

        After the function finishes the comparison, the best matches can be found as global minimums
        (when CV_TM_SQDIFF was used) or maximums (when CV_TM_CCORR or CV_TM_CCOEFF was used) using the minMaxLoc() function.
        In case of a color image, template summation in the numerator and each sum in the denominator is done over all of the
        channels and separate mean values are used for each channel. That is, the function can take a color template and a color
        image. The result will still be a single-channel image, which is easier to analyze.

    */

    Mat result;
    matchTemplate(image_gray, template_image, result, CV_TM_CCOEFF_NORMED);

    /*
        Using minMaxLoc function to find the global minimum and maximum in an array.
        minMaxLoc (
        InputArray src,
		double *  	minVal,
		double *  	maxVal = 0,
		Point *  	minLoc = 0,
		Point *  	maxLoc = 0,
		InputArray  mask = noArray())

		src	input single-channel array.
        minVal	pointer to the returned minimum value; NULL is used if not required.
        maxVal	pointer to the returned maximum value; NULL is used if not required.
        minLoc	pointer to the returned minimum location (in 2D case); NULL is used if not required.
        maxLoc	pointer to the returned maximum location (in 2D case); NULL is used if not required.
        mask	optional mask used to select a sub-array.

		The function do not work with multi-channel arrays. If you need to find minimum or maximum elements across all the channels, use Mat::reshape first to reinterpret the array as single-channel. Or you may extract the particular channel using either extractImageCOI , or mixChannels , or split

        For the first two methods ( TM_SQDIFF and MT_SQDIFF_NORMED ) the best match are the lowest values. For all the others, higher values represent better matches. So, we save the corresponding value in the matchLoc variable
    */

    //double minValue, maxValue;
    vector<Point>matcheLoc; // Variable to store the point where it was found


    // Storing all indexes where the value is greater than 80 percent
    float threshold = 0.7335; // Thresh is 80 percent, if somewhere in the result mat is greater or equal to this value, is because the template has matched that place
    for(int i = result.rows - 1; i >= 0; i--) {
        for(int j = result.cols - 1; j >= 0; j--) {
            if((result.at<float>(i,j)) >= threshold) { // Greater than 80 percent
                matcheLoc.push_back(Point(j,i)); // for it not to be inverted
            }
        }
    }

    // Draw all rectangles
    for(int i = 0; i < (int)matcheLoc.size(); i++) {
        rectangle(image_bgr, matcheLoc[i], Point(matcheLoc[i].x + width_template, matcheLoc[i].y + height_template),Scalar(0,255,0), 2, LINE_8);
    }

    //Point minLocation, maxLocation;

    //minMaxLoc(result, &minValue, &maxValue, &minLocation, &maxLocation, Mat());
    //matcheLoc = maxLocation; // Since wasn't used neither TM_SQDIFF and MT_SQDIFF_NORMED.

    // Now after the match location have been found, draw a rectangle around point area
    // rectangle(image_bgr, matcheLoc, Point(matcheLoc.x + template_image.cols, matcheLoc.y + template_image.rows), Scalar(255,255,255), 2, LINE_8);

    imshow("Image", image_bgr);

    waitKey(0);
    return 0;
}
