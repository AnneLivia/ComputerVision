#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

/*
    What is an image histogram?
    It is a graphical representation of the intensity distribution
    of an image.
    It quantifies the number of pixels for each intensity value considered

    What is histogram equalization?
    It is a method that improves the contrast in an image, in order to stretch out the intensity range.

    Steps:
    Splits the image into its R, G and B planes using the function split
    Calculate the Histogram of each 1-channel plane by calling the function calcHist
    Plot the three histograms in a window
*/

int main()
{

    Mat image = imread("im.jpg", CV_LOAD_IMAGE_COLOR);
    Mat image2 = imread("_img.jpg", CV_LOAD_IMAGE_COLOR);

    cvtColor(image, image, CV_BGR2GRAY);

    // Dims: The number of parameters you want to collect data of. In this case, dims = 1 because we are only counting the intensity values of each pixel (in a greyscale image).
    // Bins: It is the number of subdivisions in each dim.
    // range: The limits for the values to be measured. In this case: range = [0,255]

    /*
        OpenCV implements the function calcHist, which calculates the histogram of a set of arrays (usually images or image planes). It can operate with up to 32 dimensions
    */

    int nBins = 255; // It has 255 bins

    float range[] = {0, 255}; // It ranges from 0 to 255
    const float* histRange = {range};

    // Splitting each channel
    vector<Mat>splitImage;
    split(image2, splitImage);

    bool uniform = true;
    bool accumulate_ = false;

    /*
        void calcHist(const Mat* images, int nimages, const int* channels, InputArray mask, OutputArray hist, int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=false )
        void calcHist(const Mat* images, int nimages, const int* channels, InputArray mask, SparseMat& hist, int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=false )


        images – Source arrays. They all should have the same depth, CV_8U or CV_32F , and the same size. Each of them can have an arbitrary number of channels.
        nimages – Number of source images.
        channels – List of the dims channels used to compute the histogram. The first array channels are numerated from 0 to images[0].channels()-1 , the second array channels are counted from images[0].channels() to images[0].channels() + images[1].channels()-1, and so on.
        mask – Optional mask. If the matrix is not empty, it must be an 8-bit array of the same size as images[i] . The non-zero mask elements mark the array elements counted in the histogram.
        hist – Output histogram, which is a dense or sparse dims -dimensional array.
        dims – Histogram dimensionality that must be positive and not greater than CV_MAX_DIMS (equal to 32 in the current OpenCV version).
        histSize – Array of histogram sizes in each dimension.
        ranges – Array of the dims arrays of the histogram bin boundaries in each dimension. When the histogram is uniform ( uniform =true), then for each dimension i it is enough to specify the lower (inclusive) boundary L_0 of the 0-th histogram bin and the upper (exclusive) boundary U_{\texttt{histSize}[i]-1} for the last histogram bin histSize[i]-1 . That is, in case of a uniform histogram each of ranges[i] is an array of 2 elements. When the histogram is not uniform ( uniform=false ), then each of ranges[i] contains histSize[i]+1 elements: L_0, U_0=L_1, U_1=L_2, ..., U_{\texttt{histSize[i]}-2}=L_{\texttt{histSize[i]}-1}, U_{\texttt{histSize[i]}-1} . The array elements, that are not between L_0 and U_{\texttt{histSize[i]}-1} , are not counted in the histogram.
        uniform – Flag indicating whether the histogram is uniform or not (see above).
        accumulate – Accumulation flag. If it is set, the histogram is not cleared in the beginning when it is allocated. This feature enables you to compute a single histogram from several sets of arrays, or to update the histogram in time.

    */

    Mat histogram_blueChannel, histogram_redChannel, histogram_greenChannel;
    // Calculating each histogram, it takes the blue channel, number of source images 1, number of channels, 0,  mask, where will be output the hist, and so on.
    calcHist(&splitImage[0], 1, 0, Mat(), histogram_blueChannel, 1, &nBins, &histRange, uniform, accumulate_); // Blue channel histogram
    calcHist(&splitImage[1], 1, 0, Mat(), histogram_greenChannel, 1, &nBins, &histRange, uniform, accumulate_); // Green channel histogram
    calcHist(&splitImage[2], 1, 0, Mat(), histogram_redChannel, 1, &nBins, &histRange, uniform, accumulate_); // Red channel histogram

    // Draw the histogram for B, G, and R
    int hist_width = 512;
    int hist_height = 400;

    int bin_width = cvRound( (double) hist_width / nBins);

    // Black image, of 3 channels, 8 bits, with height 400 and width 512
    Mat histImage(hist_height, hist_width, CV_8UC3, Scalar(0,0,0));

    /*
        Normalize histogram:
        Normalize an histogram is a technique consisting into transforming the discrete
        distribution of intensities into a discrete distribution of probabilities.
        To do so, we need to divide each value of the histogram by the number of pixel. Because a
        digital image is a discrete set of values that could be seen as a matrix and it's equivalent to divide each
        nk by the dimension of the array which is the product of the width by the length of the image.

        void normalize(InputArray src, OutputArray dst, double alpha=1, double beta=0, int norm_type=NORM_L2, int dtype=-1, InputArray mask=noArray() )

        src – input array.
        dst – output array of the same size as src .
        alpha – norm value to normalize to or the lower range boundary in case of the range normalization.
        beta – upper range boundary in case of the range normalization; it is not used for the norm normalization.
        normType – normalization type (see the details below).
        dtype – when negative, the output array has the same type as src; otherwise, it has the same number of channels as src and the depth =CV_MAT_DEPTH(dtype).
        mask – optional operation mask.
    */

    // Normalize all the results
    normalize(histogram_blueChannel, histogram_blueChannel, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(histogram_greenChannel, histogram_greenChannel, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(histogram_redChannel, histogram_redChannel, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    // Draw for each channel using a line that takes two points, color, thickness, line type...
    for(int i = 0; i < nBins; i++) {

        line(histImage, Point(bin_width * (i - 1), hist_height - cvRound(histogram_blueChannel.at<float>(i-1))),
             Point( bin_width*(i), hist_height - cvRound(histogram_blueChannel.at<float>(i)) ), Scalar(255, 0, 0), 2, 8);

        line(histImage, Point(bin_width * (i - 1), hist_height - cvRound(histogram_greenChannel.at<float>(i-1))),
             Point( bin_width*(i), hist_height - cvRound(histogram_greenChannel.at<float>(i)) ), Scalar(0, 255, 0), 2, 8);

        line(histImage, Point(bin_width * (i - 1), hist_height - cvRound(histogram_redChannel.at<float>(i-1))),
             Point( bin_width*(i), hist_height - cvRound(histogram_redChannel.at<float>(i)) ), Scalar(0, 0, 255), 2, 8);
    }

    /*
        Equalizes the histogram of a grayscale image.
        void equalizeHist(InputArray src, OutputArray dst)
        src – Source 8-bit single channel image.
        dst – Destination image of the same size and type as src

        The function equalizes the histogram of the input image using the following algorithm:
        Calculate the histogram H for src .
        Normalize the histogram so that the sum of histogram bins is 255
        Compute the integral of the histogram.

        The algorithm normalizes the brightness and increases the contrast of the image.

        Histogram equalization is a method to process images in order to adjust the contrast of an
        image by modifying the intensity distribution of the histogram. The objective of this technique
        is to give a linear trend to the cumulative probability function associated to the image.
    */

    Mat dst;

    // Apply histogram equalization
    equalizeHist(image, dst);

    imshow("Before Equalize", image);
    imshow("After Equalize", dst);

    namedWindow("Canada Flag", CV_WINDOW_NORMAL);
    resizeWindow("Canada Flag", 600, 400);
    imshow("Canada Flag", image2);
    imshow("Histogram", histImage);
    waitKey(0);
    return 0;
}
