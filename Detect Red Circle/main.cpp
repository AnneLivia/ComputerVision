#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat image = imread("circles.jpg",CV_LOAD_IMAGE_COLOR);
    Mat hsvImage;

    if(!image.data) {
        cout << "Error loading image\n";
        return -1;
    }

    // Converting image to hsv which becomes more easier to find the color
    //  allow to identify a particular color using a single value, the hue, instead of three values.
    cvtColor(image,hsvImage,CV_BGR2HSV);

    // Threshold the hsv image, keep only the red pixels
    Mat lowerRedImageHue, upperRedImageHue;

    inRange(hsvImage,Scalar(0,100,100),Scalar(10,255,255), lowerRedImageHue);
    inRange(hsvImage,Scalar(160,100,100), Scalar(179, 255, 255), upperRedImageHue);


    // Next step is to combine the above threshold images and slightly blur the result, in order to avoid false positives
    // Combine the two image

    Mat images_redHue;
    addWeighted(lowerRedImageHue,1.0,upperRedImageHue,1.0,0.0,images_redHue);

    // Bur image
    GaussianBlur(images_redHue,images_redHue,Size(9,9),2,2);

    // To find the read circles, we can use the circle hough transform, which is implemented in opencv as HoughCircles
    /*
        The circle Hough Transform (CHT) is a basic technique used in Digital Image Processing, for detecting circular objects in a digital image.

        Houghcircles: Finds circles in a grayscale image using the Hough transform.

        void HoughCircles(InputArray image, OutputArray circles, int method, double dp, double minDist, double param1=100, double param2=100, int minRadius=0, int maxRadius=0 )

        image – 8-bit, single-channel, grayscale input image.
        circles – Output vector of found circles. Each vector is encoded as a 3-element floating-point vector (x, y, radius) .
        circle_storage – In C function this is a memory storage that will contain the output sequence of found circles.
        method – Detection method to use. Currently, the only implemented method is CV_HOUGH_GRADIENT , which is basically 21HT , described in [Yuen90].
        dp – Inverse ratio of the accumulator resolution to the image resolution. For example, if dp=1 , the accumulator has the same resolution as the input image. If dp=2 , the accumulator has half as big width and height.
        minDist – Minimum distance between the centers of the detected circles. If the parameter is too small, multiple neighbor circles may be falsely detected in addition to a true one. If it is too large, some circles may be missed.
        param1 – First method-specific parameter. In case of CV_HOUGH_GRADIENT , it is the higher threshold of the two passed to the Canny() edge detector (the lower one is twice smaller).
        param2 – Second method-specific parameter. In case of CV_HOUGH_GRADIENT , it is the accumulator threshold for the circle centers at the detection stage. The smaller it is, the more false circles may be detected. Circles, corresponding to the larger accumulator values, will be returned first.
        minRadius – Minimum circle radius.
        maxRadius – Maximum circle radius.


    */

    vector<cv::Vec3f> circles;
    HoughCircles(images_redHue,circles,CV_HOUGH_GRADIENT,1,images_redHue.rows/8, 100, 20, 0, 0);

    if(circles.empty()) {
        cout << "There's not image!\n";
        return -1;
    }

    for(size_t current_circle = 0; current_circle < circles.size(); current_circle++) {
        Point center(round(circles[current_circle][0]), round(circles[current_circle][1]));
        int radius = round(circles[current_circle][2]);

        circle(image,center,radius,Scalar(0,255,0),5);
    }
    namedWindow("Red Circle", CV_WINDOW_AUTOSIZE);

    imshow("Red Circle", image);


    waitKey();

    return 0;
}
