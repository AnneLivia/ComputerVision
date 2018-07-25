#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/*
    Thresholding is a image processing method used to convert a grey scale image
    (value of pixels ranging from 0-255) into binary image (value of pixels can have only 2 values: 0 or 1).

*/

int main() {

  Mat im = imread("images/horse6.jpg",CV_LOAD_IMAGE_COLOR);
  Mat imGray, threshImage, outImage, maskInv;

  int threshold_value = 238;
  int const max_BINARY_value = 255;
  int threshold_type = 1;

  // Convert the image to Gray
  cvtColor( im, imGray, CV_BGR2GRAY);
  // Create Threshold
  threshold( imGray, threshImage, threshold_value, max_BINARY_value,THRESH_BINARY);
  // Invert threshold
  bitwise_not(threshImage,maskInv);
  // Crop
  bitwise_and(im,im,outImage,maskInv = maskInv);

  namedWindow("Horse", WINDOW_FREERATIO);
  imshow("Horse",outImage);

  waitKey();
}

