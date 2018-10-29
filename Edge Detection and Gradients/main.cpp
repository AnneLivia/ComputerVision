#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
    An image gradient is a directional change in the intensity
    or color in an image. The gradient of the image is one of the
    fundamental building blocks in image processing.
    For example the Canny edge detector uses image gradient for edge detection.

    Edge detection is an image processing technique for
    finding the boundaries of objects within images.
    It works by detecting discontinuities in brightness.
    Edge detection is used for image segmentation and
    data extraction in areas such as image processing,
    computer vision, and machine vision.
*/

int main()
{
    VideoCapture cap(0);

    Mat frame;
    while(1) {

        cap.read(frame);

        /*
            void Laplacian(InputArray src, OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, int borderType=BORDER_DEFAULT )

            src – Source image.
            dst – Destination image of the same size and the same number of channels as src .
            ddepth – Desired depth of the destination image.
            ksize – Aperture size used to compute the second-derivative filters. See getDerivKernels() for details. The size must be positive and odd.
            scale – Optional scale factor for the computed Laplacian values. By default, no scaling is applied. See getDerivKernels() for details.
            delta – Optional delta value that is added to the results prior to storing them in dst .
            borderType – Pixel extrapolation method. See borderInterpolate() for details.

        */
        Mat lapla;
        Laplacian(frame, lapla, CV_64F);

        /*
            Sobel( InputArray src, OutputArray dst, int ddepth,
                   int dx, int dy, int ksize = 3,
                   double scale = 1, double delta = 0,
                   int borderType = BORDER_DEFAULT );
        */

        Mat sobx, soby;
        Sobel(frame, sobx, CV_64F, 1, 0, 5);
        Sobel(frame, soby, CV_64F, 0, 1, 5);

        /*
            canny edge detector
            Canny( InputArray image, OutputArray edges,
                   double threshold1, double threshold2,
                   int apertureSize = 3, bool L2gradient = false
        */

        Mat edges;
        Canny(frame, edges, 100, 200); // greater the number, more edges, lesser, less edges, more noise

        imshow("Frame", frame);
        imshow("Laplacian", lapla);
        imshow("Sobel X", sobx);
        imshow("Sobel Y", soby);
        imshow("Canny", edges);

        if(waitKey(1) >= 0)
            break;
    }
    return 0;
}
