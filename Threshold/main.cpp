#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
    Thresholding is a image processing method used to convert a grey scale image
    (value of pixels ranging from 0-255) into binary image (value of pixels can have only 2 values: 0 or 1).

    If pixel value is greater than a threshold value,
    it is assigned one value (may be white), else it is assigned another value (may be black).
    The function used is threshold.
    First argument is the source image, which should be a grayscale image.
    Second argument is the threshold value which is used to classify the pixel values.
    Third argument is the maxVal which represents the value to be given if pixel value is more than (sometimes less than) the threshold value.
    OpenCV provides different styles of thresholding and it is decided by the fourth parameter of the function.

    THRESH_BINARY
        dst(x,y) = maxval if src(x,y) > thresh; 0 otherwise;
    THRESH_BINARY_INV
        dst(x,y) = 0 if src(x,y) > thresh; maxval otherwise;
    THRESH_TRUNC
        dst(x,y) = threshold if src(x,y) > thresh; src(x,y) otherwise;
    THRESH_TOZERO
        dst(x,y) = src(x,y) if src(x,y) > thresh; 0 otherwise;
    THRESH_TOZERO_INV
        dst(x,y) = 0 if src(x,y) > thresh; src(x,y) otherwise;


    The function applies fixed-level thresholding to a single-channel array.
    The function is typically used to get a bi-level (binary) image out of a grayscale image
    or for removing a noise, that is, filtering out pixels with too small or too large values.

    the special value THRESH_OTSU may be combined with one of the above values.
    In this case, the function determines the optimal threshold value using the Otsu’s algorithm
    and uses it instead of the specified thresh . The function returns the computed threshold value.
    Currently, the Otsu’s method is implemented only for 8-bit images.
*/

int main()
{

    Mat image = imread("ball.jpg",CV_LOAD_IMAGE_COLOR);
    Mat grayImage;
    // Converting the image to gray, since to threshold the image, it has to be in gray scale
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    Mat threshBinary, threshBinary_inv, threshTrunc, threshTozero, threshTozero_inv;

    // Two outputs are obtained. First one is a retval and the second output is the thresholded image.
    // retVal = Its use comes when we go for Otsu’s Binarization.
    /*
        In the first section, I told you there is a second parameter retVal. Its use comes when we go for Otsu’s Binarization. So what is it?
        In global thresholding, we used an arbitrary value for threshold value, right? So, how can we know a value we selected is good or not? Answer is, trial and error method. But consider a bimodal image (In simple words, bimodal image is an image whose histogram has two peaks). For that image, we can approximately take a value in the middle of those peaks as threshold value, right ? That is what Otsu binarization does. So in simple words, it automatically calculates a threshold value from image histogram for a bimodal image. (For images which are not bimodal, binarization won’t be accurate.)
        For this, our cv2.threshold() function is used, but pass an extra flag, cv2.THRESH_OTSU. For threshold value, simply pass zero. Then the algorithm finds the optimal threshold value and returns you as the second output, retVal. If Otsu thresholding is not used, retVal is same as the threshold value you used.
    */

    /// Simple threshold

    threshold(grayImage,threshBinary,127,255,THRESH_BINARY);
    threshold(grayImage,threshBinary_inv,127,255,THRESH_BINARY_INV);
    threshold(grayImage,threshTrunc,127,255,THRESH_TRUNC);
    threshold(grayImage,threshTozero,127,255,THRESH_TOZERO);
    threshold(grayImage,threshTozero_inv,127,255,THRESH_TOZERO_INV);

    /*
    imshow("Original Image", image);
    imshow("Binary", threshBinary);
    imshow("Binary Inverse", threshBinary_inv);
    imshow("Trunc", threshTrunc);
    imshow("Tozero", threshTozero);
    imshow("Tozero inverse", threshTozero_inv);
    */

    /// Adaptive threshold
    /*
        The adaptive threshold, does not use a global value as in the simple threshold above.
        Since a global value may not be good in all the conditions where image has different lighting conditions,
        In this, the algorithm calculate the threshold for a small regions of the image. So we get different thresholds
        for different regions of the same image and it gives us better results for images with varying illumination.
        It has three ‘special’ input params and only one output argument.

        Adaptive Method - It decides how thresholding value is calculated.
        ADAPTIVE_THRESH_MEAN_C : threshold value is the mean of neighbourhood area
        ADAPTIVE_THRESH_GAUSSIAN_C : threshold value is the weighted sum of neighbourhood values where weights are a gaussian window.

        Block Size - It decides the size of neighbourhood area.

        C - It is just a constant which is subtracted from the mean or weighted mean calculated.

        void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)

        Parameters:

        src = Source 8-bit single-channel image.
        dst = Destination image of the same size and the same type as src .
        maxValue = Non-zero value assigned to the pixels for which the condition is satisfied. See the details below.
        adaptiveMethod = Adaptive thresholding algorithm to use, ADAPTIVE_THRESH_MEAN_C or ADAPTIVE_THRESH_GAUSSIAN_C .

        ADAPTIVE_THRESH_MEAN_C , the threshold value T(x,y) is a mean of the neighborhood of (x, y) minus C.

        ADAPTIVE_THRESH_GAUSSIAN_C , the threshold value T(x, y) is a weighted sum (cross-correlation with a Gaussian window) of the neighborhood of (x, y) minus C.
        The default sigma (standard deviation) is used for the specified blockSize

        thresholdType = Thresholding type that must be either THRESH_BINARY or THRESH_BINARY_INV .
        blockSize = Size of a pixel neighborhood that is used to calculate a threshold value for the pixel: 3, 5, 7, and so on.
        C = Constant subtracted from the mean or weighted mean (see the details below). Normally, it is positive but may be zero or negative as well.
    */

    Mat imageBur, threshAdaptive_gaussian, threshAdaptive_mean;
    // The median bur is a linear filter
    // Smoothing, also called blurring, is a simple and frequently used image processing operation.
    // There are many reasons for smoothing. In this tutorial we will focus on smoothing in order to reduce noise (other uses will be seen in the following tutorials).
    // ksize = aperture linear size; it must be odd and greater than 1, for example: 3, 5, 7 ...
    // The function smoothes an image using the median filter with the \texttt{ksize} \times \texttt{ksize} aperture. Each channel of a multi-channel image is processed independently. In-place operation is supported.
    medianBlur(grayImage,imageBur,5);

    // Simple threshold
    threshold(imageBur,threshBinary,127,255,THRESH_BINARY);

    // Adaptive thresholds

    adaptiveThreshold(imageBur,threshAdaptive_mean,255,ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2);
    adaptiveThreshold(imageBur,threshAdaptive_gaussian,255,ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);

    imshow("Original Image",image);
    imshow("Simple Thresh",threshBinary);
    imshow("Mean",threshAdaptive_mean);
    imshow("Gaussian",threshAdaptive_gaussian);

    waitKey();
    return 0;
}
