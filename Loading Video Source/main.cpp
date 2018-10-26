#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{

    VideoCapture cap(0); // Open default camera

    if(!cap.isOpened()) // Check if succeeded
        return -1;

    /*
    Mat edges;

    namedWindow("edges",1);

    while(1) {
        Mat frame; // Take the frame
        cap >> frame; // get a new frame from camera

        cvtColor(frame,edges,COLOR_BGR2GRAY); // Converting frame (color) to edge (gray)
        /*
            Gaussian Blur:
            C++: void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT )

            src – input image; the image can have any number of channels, which are processed independently, but the depth should be CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
            dst – output image of the same size and type as src.
            ksize – Gaussian kernel size. ksize.width and ksize.height can differ but they both must be positive and odd. Or, they can be zero’s and then they are computed from sigma* .
            sigmaX – Gaussian kernel standard deviation in X direction.
            sigmaY – Gaussian kernel standard deviation in Y direction; if sigmaY is zero, it is set to be equal to sigmaX, if both sigmas are zeros, they are computed from ksize.width and ksize.height , respectively (see getGaussianKernel() for details); to fully control the result regardless of possible future modifications of all this semantics, it is recommended to specify all of ksize, sigmaX, and sigmaY.
            borderType – pixel extrapolation method (see borderInterpolate() for details).

            The function convolves the source image with the specified Gaussian kernel
        */
    /*
        GaussianBlur(edges,edges,Size(7,7),1.5,1.5);

        /*
            Finds edges in an image using the [Canny86] algorithm.
            void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false )

            image – single-channel 8-bit input image.
            edges – output edge map; it has the same size and type as image .
            threshold1 – first threshold for the hysteresis procedure.
            threshold2 – second threshold for the hysteresis procedure.
            apertureSize – aperture size for the Sobel() operator.
            L2gradient – a flag, indicating whether a more accurate L_2 norm =\sqrt{(dI/dx)^2 + (dI/dy)^2} should be used to calculate the image gradient magnitude ( L2gradient=true ), or whether the default L_1 norm =|dI/dx|+|dI/dy| is enough ( L2gradient=false ).

            The function finds edges in the input image image and marks them in the output map edges using the Canny algorithm. The smallest value between threshold1 and threshold2 is used for edge linking. The largest value is used to find initial segments of strong edges.

        Canny(edges,edges,0,30,3);
        imshow("edges",edges);
        if(waitKey(30) >= 0)
            break;
    }
    */

    Mat frame; // Get frames
    Mat gray;

    while(true) {
        /*
            The methods/functions combine VideoCapture::grab and VideoCapture::retrieve in one call. This is the most convenient method for reading video files or capturing data from decode and return the just grabbed frame. If no frames has been grabbed (camera has been disconnected, or there are no more frames in video file), the methods return false and the functions return NULL pointer.
        */

        cap.read(frame);

        /*
            PutText: Draws a text string.
            void putText(Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color, int thickness=1, int lineType=8, bool bottomLeftOrigin=false )

            img – Image.
            text – Text string to be drawn.
            org – Bottom-left corner of the text string in the image.
            font – CvFont structure initialized using InitFont().
            fontFace – Font type. One of FONT_HERSHEY_SIMPLEX, FONT_HERSHEY_PLAIN, FONT_HERSHEY_DUPLEX, FONT_HERSHEY_COMPLEX, FONT_HERSHEY_TRIPLEX, FONT_HERSHEY_COMPLEX_SMALL, FONT_HERSHEY_SCRIPT_SIMPLEX, or FONT_HERSHEY_SCRIPT_COMPLEX, where each of the font ID’s can be combined with FONT_ITALIC to get the slanted letters.
            fontScale – Font scale factor that is multiplied by the font-specific base size. (change the size)
            color – Text color.
            thickness – Thickness of the lines used to draw a text.
            lineType – Line type. See the line for details.
            bottomLeftOrigin – When true, the image data origin is at the bottom-left corner. Otherwise, it is at the top-left corner.

        */

        putText(frame,"Writing Text", Point(0,130), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(200,255,255),2,LINE_8);

        cvtColor(frame,gray,COLOR_BGR2GRAY);

        imshow("Frame", frame); // Show frame
        imshow("Gray", gray);

        if(waitKey(30) >= 0)
            break;
    }


    return 0;
}



