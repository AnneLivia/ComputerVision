#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
    Morphological transformations are some simple operations based on
    the image shape, it is normally performed on binary images. and It needs
    two inputs, one is the original image and the second one is called structuring element or kernel
    which decides the nature of operation. Two basics morphological operations are Erosion and Dilatation.
    Then its variant forms like Opening, Closing, Gradient, etc. also comes into play.

*/

int main()
{
    VideoCapture cap(0);


    Mat frame;

    while(1) {

        cap.read(frame);

        Mat hsvFrame;
        cvtColor(frame,hsvFrame,CV_BGR2HSV);

        Scalar lowerRed = Scalar(160, 100, 100);
        Scalar upperRed = Scalar(179, 255, 255);


        // Creating a mask using a color red
        Mat redMask;
        inRange(hsvFrame, lowerRed, upperRed, redMask);


        // Doing background subtraction using bitwise and
        Mat result;
        bitwise_and(frame, frame, result, redMask = redMask);

        /*
            Erosion shrinks image objects while dilation expands them.

            Erosion generally decreases the sizes of objects and removes small anomalies by subtracting objects with a radius smaller than the structuring element.
            With grayscale images, erosion reduces the brightness (and therefore the size) of bright objects on a dark background by taking the neighborhood minimum when passing the structuring element over the image.
            With binary images, erosion completely removes objects smaller than the structuring element and removes perimeter pixels from larger image objects.
            The basic idea of erosion is just like soil erosion only, it erodes away the boundaries of foreground object (Always try to keep foreground in white). So what it does? The kernel slides through the image (as in 2D convolution). A pixel in the original image (either 1 or 0) will be considered 1 only if all the pixels under the kernel is 1, otherwise it is eroded (made to zero).
            So what happends is that, all the pixels near boundary will be discarded depending upon the size of kernel. So the thickness or size of the foreground object decreases or simply white region decreases in the image. It is useful for removing small white noises (as we have seen in colorspace chapter), detach two connected objects etc.

            void erode(InputArray src, OutputArray dst, InputArray kernel, Point anchor=Point(-1,-1), int iterations=1, int borderType=BORDER_CONSTANT, const Scalar& borderValue=morphologyDefaultBorderValue() )

            src – input image; the number of channels can be arbitrary, but the depth should be one of CV_8U, CV_16U, CV_16S, CV_32F` or ``CV_64F.
            dst – output image of the same size and type as src.
            element – structuring element used for erosion; if element=Mat() , a 3 x 3 rectangular structuring element is used.
            anchor – position of the anchor within the element; default value (-1, -1) means that the anchor is at the element center.
            iterations – number of times erosion is applied.
            borderType – pixel extrapolation method (see borderInterpolate() for details).
            borderValue – border value in case of a constant border (see createMorphologyFilter() for details).


        */

        Mat kernel = Mat::ones(Size(5,5), CV_8U); // Kernel can be of any size

        Mat erosion;
        erode(redMask, erosion, kernel, Point(-1,-1), 1);

        /*
            Dilation expands the image
            Dilation generally increases the sizes of objects, filling in holes and broken areas, and connecting areas that are separated by spaces smaller than the size of the structuring element.
            With grayscale images, dilation increases the brightness of objects by taking the neighborhood maximum when passing the structuring element over the image.
            With binary images, dilation connects areas that are separated by spaces smaller than the structuring element and adds pixels to the perimeter of each image object.

            void dilate(InputArray src, OutputArray dst, InputArray kernel, Point anchor=Point(-1,-1), int iterations=1, int borderType=BORDER_CONSTANT, const Scalar& borderValue=morphologyDefaultBorderValue() )

            src – input image; the number of channels can be arbitrary, but the depth should be one of CV_8U, CV_16U, CV_16S, CV_32F` or ``CV_64F.
            dst – output image of the same size and type as src.
            element – structuring element used for dilation; if element=Mat() , a 3 x 3 rectangular structuring element is used.
            anchor – position of the anchor within the element; default value (-1, -1) means that the anchor is at the element center.
            iterations – number of times dilation is applied.
            borderType – pixel extrapolation method (see borderInterpolate() for details).
            borderValue – border value in case of a constant border (see createMorphologyFilter() for details).

        */

        Mat dilation;
        dilate(redMask, dilation, kernel, Point(-1,-1), 1);
        /*
            In both, open, close, gradient, top had, black hat, etc. the function used is
            void morphologyEx(InputArray src, OutputArray dst, int op, InputArray kernel, Point anchor=Point(-1,-1), int iterations=1, int borderType=BORDER_CONSTANT, const Scalar& borderValue=morphologyDefaultBorderValue() )

            src – Source image. The number of channels can be arbitrary. The depth should be one of CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
            dst – Destination image of the same size and type as src .
            element – Structuring element.
            op – Type of a morphological operation that can be one of the following:
                MORPH_OPEN - an opening operation
                MORPH_CLOSE - a closing operation
                MORPH_GRADIENT - a morphological gradient
                MORPH_TOPHAT - “top hat”
                MORPH_BLACKHAT - “black hat”
                MORPH_HITMISS - “hit and miss”
            iterations – Number of times erosion and dilation are applied.
            borderType – Pixel extrapolation method. See borderInterpolate() for details.
            borderValue – Border value in case of a constant border. The default value has a special meaning. See createMorphologyFilter() for details.

            The function can perform advanced morphological transformations using an erosion and dilation as basic operations.

        */

        /*

            Opening: remove false positives.
            Useful for removing small objects (it is assumed that the objects are bright on a dark foreground)

            Basic idea: remove noise from the background
        */

        Mat opening;
        morphologyEx(redMask, opening, MORPH_OPEN, kernel);

        /*
            Closing: remove false negatives.
            It is useful in closing small holes inside the foreground objects, or small black points on the object.

            Basic idea: remove noise in the object
        */

        Mat closing;
        morphologyEx(redMask, closing, MORPH_CLOSE, kernel);

        /*
            Top hat: It is the difference between an input image and its opening.
        */

        Mat tophat;
        morphologyEx(redMask, tophat, MORPH_TOPHAT, kernel);

        /*
            Black hat: It is the difference between the closing and its input image
        */

        Mat blackhat;
        morphologyEx(redMask, blackhat, MORPH_BLACKHAT, kernel);

        /*
            Morphological gradient: It is the difference between the dilation and the erosion of an image.
            It is useful for finding the outline of an object
        */

        Mat gradMorph;
        morphologyEx(redMask, gradMorph, MORPH_GRADIENT, kernel);

        imshow("Real Video", frame);
        //imshow("Mask", redMask);
        imshow("Result", result);
        //imshow("Erosion", erosion);
        //imshow("Dilation", dilation);
        //imshow("Closing", closing);
        //imshow("Opening", opening);
        imshow("Top hat", tophat);
        imshow("Black hat", blackhat);
        imshow("Gradient", gradMorph);

        if(waitKey(1) >= 0) // If any key is pressed, break.
            break;
    }

    return 0;
}
