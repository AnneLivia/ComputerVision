#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
    In order to remove noise, we need to blur and smooth the image

*/
int main()
{
    VideoCapture cap(0);

    Mat frame, imageRedMask, result; // Mat for frame, frame conversion to HSV color space, mat for the red mask and for the result

    while(true) {
        cap.read(frame);
        Mat hsvFrame;
        cvtColor(frame,hsvFrame, CV_BGR2HSV);

        // H - hue, s - saturation, v - value
        Scalar lowerRed = Scalar(160,100,100);
        Scalar upperRed = Scalar(179,255,255);

        // Getting the mask of color red
        inRange(hsvFrame, lowerRed, upperRed, imageRedMask);

        // Removing background of it

        bitwise_and(frame, frame, result, imageRedMask = imageRedMask);

        // ** first way to smoothing an image by creating a mean

        // First create a kernel 15 x 15 of float
        Mat kernel = Mat::ones(Size(15,15), CV_32F) / 225;

        // Smoothing an image using the kernel above with the use of filter2D function

        Mat smoothed;

        /*
            filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );

            src: Source image
            dst: Destination image
            ddepth: The depth of dst. A negative value (such as -1) indicates that the depth is the same as the source.
            kernel: The kernel to be scanned through the image
            anchor: The position of the anchor relative to its kernel. The location Point(-1, -1) indicates the center by default.
            delta: A value to be added to each pixel during the convolution. By default it is 0
            BORDER_DEFAULT: We let this value by default (more details in the following tutorial)

        */

        filter2D(result, smoothed, -1, kernel);

        // --------------------------------------------------------------------------------------------------------

        // ** Using the function and method Gaussian blur to smoothing the image
        /*
            Gaussian Blur
            void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT )

            src – input image; the image can have any number of channels, which are processed independently, but the depth should be CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
            dst – output image of the same size and type as src.
            ksize – Gaussian kernel size. ksize.width and ksize.height can differ but they both must be positive and odd. Or, they can be zero’s and then they are computed from sigma* .
            sigmaX – Gaussian kernel standard deviation in X direction.
            sigmaY – Gaussian kernel standard deviation in Y direction; if sigmaY is zero, it is set to be equal to sigmaX, if both sigmas are zeros, they are computed from ksize.width and ksize.height , respectively (see getGaussianKernel() for details); to fully control the result regardless of possible future modifications of all this semantics, it is recommended to specify all of ksize, sigmaX, and sigmaY.
            borderType – pixel extrapolation method (see borderInterpolate() for details).

            The function convolves the source image with the specified Gaussian kernel. In-place filtering is supported.

        */
        Mat blur;
        GaussianBlur(result, blur, Size(15,15), 0);

        // --------------------------------------------------------------------------------------------------------

        // ** Median Blur
        /*
            The Median filter is a common technique for smoothing. Median smoothinging is widely used in edge detection algorithms because under certain conditions, it preserves edges while removing noise.
            The median filter run through each element of the signal (in this case the image) and replace each pixel with the median of its neighboring pixels (located in a square neighborhood around the evaluated pixel).
            void medianBlur(InputArray src, OutputArray dst, int ksize)

            src – input 1-, 3-, or 4-channel image; when ksize is 3 or 5, the image depth should be CV_8U, CV_16U, or CV_32F, for larger aperture sizes, it can only be CV_8U.
            dst – destination array of the same size and type as src.
            ksize – aperture linear size; it must be odd and greater than 1, for example: 3, 5, 7 ...

        */
        Mat median;
        medianBlur(result, median, 15);

        // --------------------------------------------------------------------------------------------------------

        // ** Median Blur

        /*
            Bilateral blurring is one of the most advanced filter to smooth an image and reduce noise. The other three filters will smooth away the edges while removing noises, however, this filter can reduce noise of the image while preserving the edges. The drawback of this type of filter is that it takes longer to filter the input image.
            void bilateralFilter(InputArray src, OutputArray dst, int d, double sigmaColor, double sigmaSpace, int borderType=BORDER_DEFAULT )


            src – Source 8-bit or floating-point, 1-channel or 3-channel image.
            dst – Destination image of the same size and type as src .
            d – Diameter of each pixel neighborhood that is used during filtering. If it is non-positive, it is computed from sigmaSpace .
            sigmaColor – Filter sigma in the color space. A larger value of the parameter means that farther colors within the pixel neighborhood (see sigmaSpace ) will be mixed together, resulting in larger areas of semi-equal color.
            sigmaSpace – Filter sigma in the coordinate space. A larger value of the parameter means that farther pixels will influence each other as long as their colors are close enough (see sigmaColor ). When d>0 , it specifies the neighborhood size regardless of sigmaSpace . Otherwise, d is proportional to sigmaSpace .

        */
        Mat bilateralBlur;
        bilateralFilter(result, bilateralBlur, 14, 75, 75);

        imshow("Real Video", frame);
        //imshow("Mask", imageRedMask);
        imshow("Smoothed", smoothed);
        imshow("Blur", blur);
        imshow("Media Blur", median);
        imshow("Bilateral Blur", bilateralBlur);

        if(waitKey(1) >= 0)
            break;
    }
    return 0;
}
