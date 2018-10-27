#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0);

    Mat frame, hsvFrame;

    while(true) {
        cap.read(frame);

        cvtColor(frame,hsvFrame,CV_BGR2HSV);

        Mat red, green, orange, yellow, blue;
        int cred, cgreen, corange, cyellow, cblue;

        // Red
        inRange(hsvFrame,Scalar(160,100,100), Scalar(179,255,255), red);
        cred = countNonZero(red);

        // Green
        inRange(hsvFrame, Scalar(55,100,100), Scalar(70,255,255), green);
        cgreen = countNonZero(green);

        // Orange
        inRange(hsvFrame, Scalar(9, 100, 100),Scalar(29, 255, 255),orange);
        corange = countNonZero(orange);

        // Blue
        inRange(hsvFrame, Scalar(110, 100, 100), Scalar(130, 255, 255), blue);
        cblue = countNonZero(blue);

        // Yellow
        inRange(hsvFrame, Scalar(20, 100, 100), Scalar(40, 255, 255), yellow);
        cyellow = countNonZero(yellow);

        Mat result;

        String colorName = "";
        Scalar color;
        if(cred > cgreen && cred > corange && cred > cblue) {
            bitwise_and(frame, frame, result, red = red);
            colorName = "Red";
            color = Scalar(0,0,255);
        } else if (cgreen > cred && cgreen > corange && cgreen > cblue){
            bitwise_and(frame,frame, result, green = green);
            colorName = "Green";
            color = Scalar(0,255,0);
        } else if (corange > cred && corange > cgreen && corange > cblue) {
            bitwise_and(frame, frame, result, orange = orange);
            colorName = "Orange";
            color = Scalar(3,122,254);
        } else if(cblue > cred && cblue > corange && cblue > cgreen){
            bitwise_and(frame, frame, result, blue = blue);
            colorName = "Blue";
            color = Scalar(255,0,0);
        } else if (cyellow > cred && cyellow > cblue && cyellow > cgreen && cyellow > corange) {
            bitwise_and(frame, frame, result, yellow = yellow);
            colorName = "Yellow";
            color = Scalar(0,255,255);
        } else {
            colorName = "";
            color = Scalar(0,0,0);
        }

        // cout << corange << " " << cred << " " << cblue << " " << cgreen << endl;

        putText(frame,colorName,Point(frame.cols/6,frame.rows/5),FONT_HERSHEY_SIMPLEX, 4, color, 4, LINE_AA);

        imshow("video", frame);


        if(waitKey(1) >= 0)
            break;
    }
    return 0;
}
