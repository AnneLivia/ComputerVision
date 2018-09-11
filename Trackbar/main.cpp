#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void on_trackbar(int, void*) {

}

int main()
{
    VideoCapture cap(0);

    Mat frame;

    // The window must be created so that it can be used with a trackbar

    // namedWindow("Frame", CV_WINDOW_AUTOSIZE);

    /*
        The function to create a trackbar and attaches it to the specified window is:

        int createTrackbar(const string& trackbarname, const string& winname, int* value, int count, TrackbarCallback onChange=0, void* userdata=0)
        Where its parameters are:

        trackbarname – Name of the created trackbar.
        winname – Name of the window that will be used as a parent of the created trackbar.
        value – Optional pointer to an integer variable whose value reflects the position of the slider. Upon creation, the slider position is defined by this variable.
        count – Maximal position of the slider. The minimal position is always 0.
        onChange – Pointer to the function to be called every time the slider changes position. This function should be prototyped as void Foo(int,void*); , where the first parameter is the trackbar position and the second parameter is the user data (see the next parameter). If the callback is the NULL pointer, no callbacks are called, but only value is updated.
        userdata – User data that is passed as is to the callback. It can be used to handle trackbar events without using global variables.

        The function createTrackbar creates a trackbar (a slider or range control) with the specified name and range, assigns a variable value to be a position synchronized with the trackbar and specifies the callback function onChange to be called on the trackbar position change. The created trackbar is displayed in the specified window winname.
    */

    int valueR = 0;
    int valueG = 0;
    int valueB = 0;

    // Creating a RGB color palette
    Mat colorPallete(300, 502, CV_8UC3, Scalar(0,0,0)); // Image, 250x250, 3 channel, color black
    namedWindow("Color Palette", CV_WINDOW_AUTOSIZE);

    // TrackBar for R, G and B
    createTrackbar("Red", "Color Palette", &valueR, 255, nullptr);
    createTrackbar("Green", "Color Palette", &valueG, 255, nullptr);
    createTrackbar("Blue", "Color Palette", &valueB, 255, nullptr);
    // Creating switch (on/off)

    createTrackbar("Switch", "Color Palette", 0, 1, nullptr);

    //createTrackbar("Test", "Frame", &value, 500, nullptr);
    //createTrackbar("color/gray", "Frame", &value, 1, nullptr);

    while(true) {
        cap.read(frame);

        // In order to to in real time

        // to get the trackbar position
        //int posTrack = getTrackbarPos("Test", "Frame");

        //int swi = getTrackbarPos("color/gray", "Frame");
        //if(swi) {
        //    cvtColor(frame,frame, CV_BGR2GRAY);
        //}

        int op = getTrackbarPos("Switch", "Color Palette");
        if(op == 0) {
            colorPallete = 0;
        } else {
            colorPallete = Scalar(valueB, valueG, valueR);
        }
        // putText(frame, to_string(posTrack), Point(50, 150), FONT_HERSHEY_PLAIN, 4, Scalar(0,0,255), 2, LINE_AA);
        //  imshow("Frame", frame);

        imshow("Color Palette", colorPallete);
        if(waitKey(1) >= 0)
            break;
    }
    return 0;
}
