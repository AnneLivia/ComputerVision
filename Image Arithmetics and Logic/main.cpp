#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int main()
{
    Mat img1 = imread("image1.png",CV_LOAD_IMAGE_COLOR);
    Mat img2 = imread("image2.png",CV_LOAD_IMAGE_COLOR);

    if(!img1.data || !img2.data) {
        cout << "Error\n";
        return -1;
    }

    //imshow("Image 1", img1);
    //imshow("Image 2", img2);

    Mat add1 = img1 + img2;

    Mat add2;

    add(img1,img2, add2);

    //imshow("Add 1",add1);
    //imshow("Add 2",add2);

    Mat weighted;

    // Blending two image.
    addWeighted(img1, 0.6, img2, 0.4, 0, weighted);

    //imshow("Weighted", weighted);

    Mat logo = imread("logo.png",CV_LOAD_IMAGE_COLOR);

    int rows = logo.rows;
    int cols = logo.cols;
    int channel = logo.channels();



    Mat imageRoi = logo(Range(0,rows), Range(0,cols));

    Mat gray;

    cvtColor(logo,gray,COLOR_BGR2GRAY);

    Mat mask;
    // If the pixel value is greater than 220, it's going to be 255 (white), otherwise, (black)
    threshold(gray,mask,220,255,THRESH_BINARY);

    //imshow("Mask",mask);

    Mat inverse_mask;
    bitwise_not(mask,inverse_mask);

    imshow("Inverse Mask",inverse_mask);

    Mat img_backGround1, img_backGround2;

    bitwise_and(imageRoi,imageRoi, img_backGround1, mask = inverse_mask);
    bitwise_and(imageRoi,imageRoi, img_backGround2, mask = mask);

    imshow("Bitwise and 1",img_backGround1);
    imshow("Bitwise and 2",img_backGround2);

    Mat dst;

    add(img_backGround1, img_backGround2,dst);

    dst.copyTo(img1(Rect(0,0,dst.cols,dst.rows))); // paste the image in the other one

    imshow("DSt", img1);

    waitKey(0);
    return 0;
}
