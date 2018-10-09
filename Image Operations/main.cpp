#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("horse1.jpg",CV_LOAD_IMAGE_COLOR);

   // Vec3b px = img.at<Vec3b>(204, 200); // Getting a specific pixel

   // cout << px << endl;

    /* ROI - Region of Interest
        Select a rectangle region of interest inside the image and cut
        or display part of the image from the bigger picture.
    */

    //imshow("Image Loaded", img);

    // Doing a rectangle, starting at x = 300, y 300, width: 400, height: 400
    //Rect rec(img.cols/4,img.rows/4,200,200);
    // Drawing rectangle in the image
    //rectangle(img,rec,Scalar(255,0,0), 1, 8, 0);

    //imshow("Image with rectangle", img);

    /*
        selectROI allows to select a rectangle in an image, crop the rectangular region
        and display the cropped image.
    */

    /*
    // Select ROI
    bool fromCenter = false; // draw rectangle from the top left corner to the right left if false, otherwise is from the center.
    bool showCrossHair = false;
    // To specify a window name, just do it in the first parameter
    Rect2d r = selectROI("Image",img, fromCenter, showCrossHair); // This function return a 2d rectangle coordinates
    // Crop image
    Mat croppedImage = img(r);

    imshow("Image",croppedImage);

    */

    Rect rec(200,400,200,155);
    rectangle(img,rec,Scalar::all(255),-1,8,1);


    imshow("Image",img);
    waitKey();

    return 0;
}
