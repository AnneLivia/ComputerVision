#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
    Contrast and brightness adjustments, as well as, color correction and transformation are
    example of pixel transform (point operator), where, according to the opencv documentation:
    In this kind of image processing transform, each output pixel’s value depends on only the
    corresponding input pixel value (plus, potentially, some globally collected information or parameters).
    Point processing methods:
    - Intersity transformations that convert an old pixel into a new based on some predefined function
    - They operate on a pixel based solely on that pixel's value
    - Used primarily for contrast enhancement

    Addition and multiplication with a constant are two commonly used point processes g(i,j) = alpha * f(i,j) + beta
    alpha and beta are said to control contrast and brightness respectively
*/

int main()
{
    double alpha; // Contrast control
    int beta; // Brightness control

    Mat image1 = imread("horse1.jpg",CV_LOAD_IMAGE_COLOR);
    Mat image2 = imread("horse2.jpg",CV_LOAD_IMAGE_COLOR);

    if(!image1.data || !image2.data) {
        cout << "Error in the image\n";
        return -1;
    }

    Mat newImage1 = Mat::zeros(image1.size(), image2.type()); // Creating a MAT of image's size and type
    Mat newImage2 = Mat::zeros(image2.size(), image2.type()); // Creating a MAT of image's size and type

    cout << "Type the alpha value [1.0 - 3.0]: ";
    cin >> alpha;
    cout << "Type the beta value [0-100]: ";
    cin >> beta;

    // Doing manually:

    /* Saturate_cast template:
        The functions saturate_cast resemble the standard C++ cast operations, such as static_cast<T>() and others. They perform an efficient and accurate conversion from one primitive type
        to another. saturate in the name means that when the input value v is out of the range of the target type, the result is not formed just by taking low bits of the input, but instead
        the value is clipped
    */
    // To each row and column position, the operation newImage(i,j) = alpha * image(i,j) + beta, will be done.
    for (int i = 0; i < image1.rows; i++) { // Transversing each row position of the image
        for(int j = 0; j < image1.cols; j++) { // Each column
            for(int c = 0; c < image1.channels(); c++) // each channel
                newImage1.at<Vec3b>(i,j)[c] = saturate_cast<uchar>(alpha * (image1.at<Vec3b>(i,j)[c]) + beta); // This operation can give values out of range or not integers (if alpha is a float), so the function saturate_cast is used to make sure the values are valid
        }
    }

    namedWindow("1 - Original Image",CV_WINDOW_AUTOSIZE);
    namedWindow("2 - New Image",CV_WINDOW_AUTOSIZE);

    imshow("1 - Original Image",image1);
    imshow("1 - New Image",newImage1);

    // Doing using the method convertTo that Converts an array to another data type with optional scaling.

    /*
        void Mat::convertTo(OutputArray m, int rtype, double alpha=1, double beta=0 );

        m - output matrix; if it does not have a proper size or type before the operation, it is reallocated.
        rtype - desired output matrix type or, rather, the depth since the number of channels are the same as the input has; if rtype is negative, the output matrix will have the same type as the input.
        alpha - optional scale factor.
        beta - optional delta added to the scaled values.

        The method converts source pixel values to the target data type. saturate_cast<> is applied at the end to avoid possible overflows
        m(x,y) = saturate_cast<rType> (alpha * (*this)(x,y) + beta);
    */

    image2.convertTo(newImage2,-1,alpha,beta);

    namedWindow("2 - Original Image",CV_WINDOW_AUTOSIZE);
    namedWindow("2 - New Image",CV_WINDOW_AUTOSIZE);

    imshow("2 - Original Image",image2);
    imshow("2 - New Image",newImage2);
    waitKey();
    return 0;
}
