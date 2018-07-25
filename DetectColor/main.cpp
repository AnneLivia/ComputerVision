#include <iostream>
#include <opencv2/opencv.hpp>
#include <map>

using namespace std;
using namespace cv;

/*
    Color BGR (RGB) found:

*/
int main()
{
    Mat im = imread("images/purple.jpg",CV_LOAD_IMAGE_COLOR);

    Mat colors[11];

    // Checks if array elements lie between the elements of two other arrays (upper bound and lower bound).
    // dst(i) = lowerb <= array[i] <= upperb
    // That is, dst (I) is set to 255 (all 1 -bits) if src (I) is within the specified 1D, 2D, 3D, ... box and 0 otherwise.

    /*
        Parameters
        src	first input array.
        lowerb	inclusive lower boundary array or a scalar.
        upperb	inclusive upper boundary array or a scalar.
        dst	output array of the same size as src and CV_8U type.

    */

    inRange(im,Scalar(0,0,0),Scalar(46,46,46),colors[0]); // BLACK
    inRange(im,Scalar(94,0,0),Scalar(255,51,51),colors[1]); // DARK BLUE
    inRange(im,Scalar(40,104,6),Scalar(82,207,14),colors[2]); // DARK GREEN
    inRange(im,Scalar(187,117,53),Scalar(215,160,111),colors[3]); // LIGHT BLUE
    inRange(im,Scalar(0,225,113),Scalar(83,255,159),colors[4]); // LIGHT GREEN
    inRange(im,Scalar(0,115,230),Scalar(62,158,255),colors[5]); // ORANGE
    inRange(im,Scalar(111,0,221),Scalar(174,94,255),colors[6]); // PINK
    inRange(im,Scalar(108,4,74),Scalar(245,16,171),colors[7]); // PURPLE
    inRange(im,Scalar(0,0,170),Scalar(74,74,255),colors[8]); // RED
    inRange(im,Scalar(233,233,233),Scalar(255,255,255),colors[9]); // WHITE
    inRange(im,Scalar(0,232,232),Scalar(102,255,255),colors[10]); // YELLOW

    map <string, int> nonBlackColor = {
        {"Red", 0}, {"Black", 0}, {"White", 0}, {"Light Green", 0}, {"Dark Green", 0},
        {"Yellow", 0}, {"Dark Blue", 0}, {"Light Blue", 0}, {"Purple", 0}, {"Pink", 0}, {"Orange", 0},
    };

    // Os valores estão ordenados em ordem alfabetica

    int i = 0;
    for ( auto it = nonBlackColor.begin(); it != nonBlackColor.end(); it++) {
        it->second = countNonZero(colors[i++]);
    }

    map<string,int>::iterator maior = nonBlackColor.begin(); // Find the bigger
    string color;
    for ( auto it = nonBlackColor.begin(); it != nonBlackColor.end(); it++) {
        if(maior->second < it->second)
            maior = it;
        cout << it->first << " " << it->second << endl;
    }

    namedWindow("Color: " + maior->first, WINDOW_FREERATIO);
    imshow("Color: " + maior->first,im);


    waitKey();
    return 0;
}
