#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat original = imread("horse1.jpg",CV_LOAD_IMAGE_COLOR);

    // Split each one of those channel, BGR = Blue, Green and Red

    Mat splitChannels[3]; // Array to store each channel of the image

    // split function is used to divide a multi-channel array into several single-channel arrays.
    // C++: void split(const Mat& src, Mat* mvbegin)
    // C++: void split(InputArray m, OutputArrayOfArrays mv)
    /*
        Parameters:
        SRC = input multi-channel array.
        MV = output array or vector of arrays; in the first variant of the function the number of arrays must match src.channels();
        the arrays themselves are reallocated, if needed.
    */
    // The functions split split a multi-channel array into separate single-channel arrays:
    // If you need to extract a single channel or do some other sophisticated channel permutation, use mixChannels() .
    split(original,splitChannels);
    // They are not in color, because what appear are the intensity of them.
    imshow("B",splitChannels[0]);
    imshow("G",splitChannels[1]);
    imshow("R",splitChannels[2]);

    splitChannels[2] = Mat::zeros(splitChannels[2].size(), CV_8UC1); // Replaces the red channel of the image, inside the splitchannels of the size of splitchannels[2] and of type CV_8UC1

    Mat output;

    // Merge: Creates one multichannel array out of several single-channel ones.
    // C++: void merge(const Mat* mv, size_t count, OutputArray dst)
    // C++: void merge(InputArrayOfArrays mv, OutputArray dst)¶
    /*
        Parameters:
        MV = input array or vector of matrices to be merged; all the matrices in mv must have the same size and the same depth.
        count = number of input matrices when mv is a plain C array; it must be greater than zero.
        DST = output array of the same size and the same depth as mv[0]; The number of channels will be the total number of channels in the matrix array.
    */

    merge(splitChannels,3,output);

    imshow("Merged Image",output);

    waitKey();
    return 0;
}
