#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc_c.h"

using namespace std;
using namespace cv;

/*
    According to OPENCV documentation:
    The idea about mask operations is to recalculate each pixels value
    in an image according to a mask matrix (also known as kernel). This mask holds values that will adjust how much influence neighboring pixels (and the current pixel)
    have on the new pixel value. From a mathematical point of view we make a weighted average, with our specified values.

    An image kernel is a small matrix used to apply effects such as blurring, sharpening, outlining or embossing.
    They're also used in machine learning for 'feature extraction', a technique for determining the most important portions of an image.
    In this context the process is referred to more generally as "convolution"

    An image is not isotropic.
    Neighbors: there two ways to define neighbors of a pixel p located at (x,y)

    4 neighbors N4(p) are the four pixels located at (x - 1, y), (x + 1, y),
    (x,y-1) and (x, y + 1). respectively, above (north), bellow (south), to the left (west) and right (east) of the pixel p.

    8 neighbors: N8(p) are including the 4 neighbors and other 4 pixels, that are located at the diagonal, (x - 1, y - 1) (northwest), (x - 1, y + 1) (northeast), (x+1,y-1)(southwest), (x+1,y+1) (southeast).

    some kernels matrix according to the website: http://setosa.io/ev/image-kernels/

    Blur: The blur kernel de-emphasizes differences in adjacent pixel values.
    0.0625 0.125 0.0625
    0.125 0.25 0.125
    0.0625 0.125 0.0625

    Bottom Sobel: sobel kernels are used to show only the differences in adjacent pixel values in a particular direction.
    -1 -2 -1
     0  0  0
     1  2  1

    Emboss: The emboss kernel (similar to the sobel kernel and sometimes referred to mean the same) givens the illusion of depth by emphasizing the differences of pixels in a given direction. In this case, in a direction along a line from the top left to the bottom right.
    -2 -1 0
    -1  1 1
     0  1 2

    identity: The indentity kernel leaves the image unchanged.
    0 0 0
    0 1 0
    0 0 0

    left Sobel: sobel kernels are used to show only the differences in adjacent pixel values in a particular direction.
    1 0 -1
    2 0 -2
    1 0 -1

    outline: An outline kernel (also called an "edge" kernel) is used to highlight large differences in pixel values. A pixel next to neighbor pixels with close to the same intensity will appear black in the new image while one next to neighbor pixels that differ strongly will appear white.
    -1 -1 -1
    -1  8 -1
    -1 -1 -1

    right sobel:  kernels are used to show only the differences in adjacent pixel values in a particular direction.
    -1 0 1
    -2 0 2
    -1 0 1

    sharpen: The sharpen kernel emphasizes differences in adjacent pixel values. This makes the image look more vivid.
    0 -1  0
   -1  5 -1
    0 -1  0

    top sobel: kernels are used to show only the differences in adjacent pixel values in a particular direction.
    1  2  1
    0  0  0
   -1 -2 -1

   for each 3x3 block of pixels in the image, we multiply each pixel by the corresponding entry of the kernel and then take the sum.
   That sum becomes a new pixel in the image.

*/

void sharpen(const Mat& myImage, Mat& result); // function that will sharpen an image

int main()
{
    Mat im = imread("horse1.jpg",CV_LOAD_IMAGE_COLOR);
    if(im.empty()) {
        cout << "Error! the image does not exist or the address file is wrong\n";
        return -1;
    }

    Mat imgray, imageResult1, imSharpen, imEmboss, imBlur;

    cvtColor(im,imgray,CV_BGR2GRAY); // converting the image to grayscale

    sharpen(imgray,imageResult1);

    // applying those filter using the function called filter2D
    /*
        Applying such filters are so common in image processing that
        in OpenCV there exist a function that will take care of applying
        the mask (also called a kernel in some places). For this you first need
        to define a Mat object that holds the mask:

        0 -1  0
       -1  5 -1
        0 -1  0
    */
    // Sharpen kernel
    Mat kernSharpen = (Mat_<char>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    // Emboss kernel
    Mat kernEmboss = (Mat_<char>(3,3) << -2, -1, 0, -1, 1, 1, 0, 1, 2);
    // Blur kernel
    Mat kernBlur = (Mat_<float>(3,3) << 0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625);
    /*
        Filter2D: Convolves an image with the kernel.
        The function even has a fifth optional argument to specify the center of the kernel, and a sixth one for determining what to do
        in the regions where the operation is undefined (borders).
        Using this function has the advantage that it’s shorter,
        less verbose (In computer science, 'verbose' is basically used for long lines of codes when that particular code can be written in few lines.
        Compacting the number of line for same logic.) and because there are some optimization
        techniques implemented it is usually faster than the
        hand-coded method. For example in my test while the second
        one took only 13 milliseconds the first took around 31 milliseconds.

         void filter2D(InputArray src, OutputArray dst, int ddepth, InputArray kernel, Point anchor=Point(-1,-1), double delta=0, int borderType=BORDER_DEFAULT )


         src = input image.
         dst = output image of the same size and the same number of channels as src.
         ddepth = desired depth of the destination image; if it is negative, it will be the same as src.depth()
         kernel = convolution kernel (or rather a correlation kernel), a single-channel floating point matrix; if you want to apply different kernels to different
         channels, split the image into separate color planes using split() and process them individually.
         anchor = anchor of the kernel that indicates the relative position of a filtered point within the kernel; the anchor should lie within the kernel;
         default value (-1,-1) means that the anchor is at the kernel center.
         delta = optional value added to the filtered pixels before storing them in dst
         borderType = pixel extrapolation method (see borderInterpolate() for details).

         That is, the kernel is not mirrored around the anchor point. to use a real convolution,
         flip the kernel using flip() and set the new anchor to
         (kernel.cols - anchor.x - 1, kernel.rows - anchor.y - 1).
    */
    // Sharpen filter
    filter2D(imgray,imSharpen,imgray.depth(),kernSharpen);
    // Emboss filter
    filter2D(imgray,imEmboss,imgray.depth(),kernEmboss);
    // Blur filter
    filter2D(imgray,imBlur,imgray.depth(),kernBlur);

    imshow("Original Image",im);
    imshow("Image in gray scale",imgray);
    imshow("Sharpen with Function",imageResult1);
    imshow("Sharpen", imSharpen);
    imshow("Emboss", imEmboss);
    imshow("Blur", imBlur);
    waitKey();
    return 0;
}

// Basic method: formula: I(i,j) = 5 * I(i,j) - [I(i-1,j) + I(i + 1, j) + I(i, j - 1) + I(i, j + 1)]
void sharpen(const Mat& myImage, Mat& result) {
   // CV_assert = Checks a condition at runtime and throws exception if it fails
   /*
    The macros CV_Assert (and CV_DbgAssert) evaluate the specified expression. If it is 0,
    the macros raise an error (see error() ). The macro CV_Assert checks the condition in
    both Debug and Release configurations while CV_DbgAssert is only retained in the Debug configuration.
   */

    CV_Assert(myImage.depth() == CV_8U); // Checking if the image is of type uchar (grayscale) // This function is getting an error
    if(myImage.depth() != CV_8U)
        exit(1);

    result.create(myImage.size(),myImage.type()); // Creating an image of the same size and type as the image itself

    const int nChannels = myImage.channels(); // Getting the number of channels, that depending on the number of channels we may have one or more subcolumns. We will iterate through them via pointers so the total number of elements depends from this number.

    // Bellow will be used plain C[] operator to access the pixels.
    for(int i = 1; i < myImage.rows - 1; ++i) {
        // Because will be accessed multiple rows at the same time, we’ll acquire the pointers for each of them (a previous, a current and a next line).
        const uchar* previous = myImage.ptr<uchar>(i - 1);
        const uchar* current = myImage.ptr<uchar>(i);
        const uchar* next = myImage.ptr<uchar>(i + 1);

        uchar* output = result.ptr<uchar>(i); // This is a pointer to where it is going to save the calculation.

        for(int j = nChannels; j < nChannels * (myImage.cols - 1); ++j) {
            *output++ = saturate_cast<uchar>(5 * current[j] - current[j - nChannels] - current[j + nChannels] - previous[j] - next[j]);
        }
    }

    /*
        On the borders of the image the upper notation results inexistent pixel locations (like minus one - minus one).
        In these points our formula is undefined. A simple solution is to not apply the kernel in these points and, for example,
        set the pixels on the borders to zeros:
    */

    result.row(0).setTo(Scalar(0)); // Top row set to color black
    result.row(result.rows - 1).setTo(Scalar(0)); // bottom row set to color black
    result.col(0).setTo(Scalar(0)); // left column set to black
    result.col(result.cols - 1).setTo(Scalar(0)); // right column set to black
}
