#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    /*
        Although Mat works really well as an image container,
        it is also a general matrix class. Therefore, it is
        possible to create and manipulate multidimensional matrices.
        You can create a Mat object in multiple way


        Then we need to specify the data type to use for storing the
        elements and the number of channels per matrix point. To do
        this we have multiple definitions constructed according to the following convention

        CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]

        Example: CV_8UC3 - unsigned type of 8 bit long and each pixel has 3 channels
    */

    Mat M(2,2,CV_8UC3,Scalar(0,0,255)); // Mat of size 2x2, three channels and color red
    cout << "M = " << endl << M << endl;

    cout << "\n\nMATLAB initializers: " << endl;
    Mat E = Mat::eye(4,4,CV_64F);
    Mat O = Mat::ones(2,2,CV_32F);
    Mat Z = Mat::zeros(3,3,CV_8UC1);

    cout << "\nE = " << endl << E << endl;
    cout << "\nO = " << endl << O << endl;
    cout << "\nZ = " << endl << Z << endl;

    // Comma separated initializer for small matrices
    Mat C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "\nC = " << endl << C << endl;

    // New header for an existing Mat object and use the method clone() or copyTo()
    // Clone() - Creates a full copy of the array and the underlying data.
    // Copies the matrix to another one

    Mat rowClone1 = C.row(1).clone(); // Copy the second row to the new mat object
    Mat rowClone2;
    C.copyTo(rowClone2);

    cout << "\nRowClone1 = \n " << rowClone1 << endl;
    cout << "\nRowClone2 = \n " << rowClone2 << endl;

    // Fill a mat object with random number
    Mat R = Mat(3,2,CV_8UC3);
    randu(R,Scalar::all(0), Scalar::all(255));

    cout << "\nRandom = \n " << R << endl;

    /* input formats
        FMT_DEFAULT, FMT_MATLAB, FMT_CSV, FMT_PYTHON, FMT_NUMPY, and FMT_C.
    */
    cout << "R (default) = " << endl << R << endl << endl;
    cout << "R (phyton) = " << endl << format(R,cv::Formatter::FMT_PYTHON) << endl << endl;
    cout << "R (matlab) = " << endl << format(R,cv::Formatter::FMT_MATLAB) << endl << endl;
    cout << "R (Numpy) = " << endl << format(R,cv::Formatter::FMT_NUMPY) << endl << endl;
    cout << "R (C) = " << endl << format(R,cv::Formatter::FMT_C) << endl << endl;
    cout << "R (comma separated values (csv)) " << endl << format(R,cv::Formatter::FMT_CSV) << endl << endl;
    waitKey();
    return 0;
}
