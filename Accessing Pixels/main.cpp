#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdint>

using namespace std;
using namespace cv;

int main()
{
    // Mat original = imread("horse1.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    // Mat modified = imread("horse1.jpg",CV_LOAD_IMAGE_GRAYSCALE);

    Mat original = imread("horse1.jpg",CV_LOAD_IMAGE_COLOR);
    Mat modified = imread("horse1.jpg",CV_LOAD_IMAGE_COLOR);

    // Images are made of data, and that data can have different size.
    // Can be float, size 32, double 64, and so on.
    // In order to get pixel intensity value, you have to know the type of
    // an image and the number of channels. Here is an example for a single
    // channel grey scale image (type 8UC1) and pixel coordinates x and y:
    // Scalar intensity = img.at<uchar>(y, x);
    // intensity.val[0] contains a value from 0 to 255. Note the ordering of x and y.
    // Since in OpenCV images are represented by the same structure as matrices, we
    // use the same convention for both cases - the 0-based row index (or y-coordinate)
    // goes first and the 0-based column index (or x-coordinate) follows it. Alternatively,
    // you can use the following notation:
    // Scalar intensity = img.at<uchar>(Point(x, y));
    // Char = 8 bits
    /*
        Sizes inside the file: CSTDINT
        using ::int8_t;
        using ::int16_t;
        using ::int32_t;
        using ::int64_t;

        using ::int_fast8_t;
        using ::int_fast16_t;
        using ::int_fast32_t;
        using ::int_fast64_t;

        using ::int_least8_t;
        using ::int_least16_t;
        using ::int_least32_t;
        using ::int_least64_t;

        using ::intmax_t;
        using ::intptr_t;

        using ::uint8_t;
        using ::uint16_t;
        using ::uint32_t;
        using ::uint64_t;

        using ::uint_fast8_t;
        using ::uint_fast16_t;
        using ::uint_fast32_t;
        using ::uint_fast64_t;

        using ::uint_least8_t;
        using ::uint_least16_t;
        using ::uint_least32_t;
        using ::uint_least64_t;

        using ::uintmax_t;
        using ::uintptr_t;
    */

    /* for ( int r = 0; r < modified.rows; r++) {
        for ( int c = 0; c < modified.cols; c++) {
            modified.at<uint8_t>(r,c) = modified.at<uint8_t>(r,c) * 0.5f; // Diminishing the intensity of the image
        }
    }
    */

    // A color image has 3 channels a red, green and blue, although in OpenCV, its blue, green, red.
    // To iterate over every pixel, we need a vector type, it has to iterate the three channels
    // Vec3i - int, Vec3d - double, etc.
    // to move to the green, red and blue channel, it must have brackets notation
    // modified.at<Vec3b>(r,c)[0] - blue, modified.at<Vec3b>(r,c)[1] - green, modified.at<Vec3b>(r,c)[3] - red,
    /*
        Now let us consider a 3 channel image with BGR color ordering (the default format returned by imread)
        Vec3b intensity = img.at<Vec3b>(y, x);
        uchar blue = intensity.val[0];
        uchar green = intensity.val[1];
        uchar red = intensity.val[2];
        You can use the same method for floating-point images (for example, you can get such an image by running Sobel on a 3 channel image):
        Vec3f intensity = img.at<Vec3f>(y, x);
        float blue = intensity.val[0];
        float green = intensity.val[1];
        float red = intensity.val[2];
        The same method can be used to change pixel intensities:
        img.at<uchar>(y, x) = 128;
        one can access a point in this matrix using the same method Mat::at
        Point2f point = pointsMat.at<Point2f>(i, 0);
    */

    for ( int r = 0; r < modified.rows; r++) {
        for ( int c = 0; c < modified.cols; c++) {
            modified.at<Vec3b>(r,c)[0] = modified.at<Vec3b>(r,c)[0] * 0; // get rid of the blue channel
        }
    }

    imshow("Original Image",original);
    imshow("Modified Image",modified);

    waitKey(0);

    // If we need to copy the data, this is done using, for example, Mat::copyTo or Mat::clone:
    // Mat img = imread("image.jpg");
    // Mat img1 = img.clone();
    // For example, here is how we can make a black image from an existing greyscale image img
    // img = Scalar(0);
    // Rect r(10, 10, 100, 100);
    // Mat smallImg = img(r);
    // Mat img = imread("image.jpg"); // loading a 8UC3 image
    // Mat grey;
    // cvtColor(img, grey, CV_BGR2GRAY);
    return 0;
}
