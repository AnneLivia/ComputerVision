#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void callback_function(int event, int x, int y, int flag, void* user_data) {
    /*
        event - Type of the mouse event. These are the entire list of mouse events
            EVENT_MOUSEMOVE
            EVENT_LBUTTONDOWN
            EVENT_RBUTTONDOWN
            EVENT_MBUTTONDOWN
            EVENT_LBUTTONUP
            EVENT_RBUTTONUP
            EVENT_MBUTTONUP
            EVENT_LBUTTONDBLCLK
            EVENT_RBUTTONDBLCLK
            EVENT_MBUTTONDBLCLK
    */
    if(event == EVENT_MOUSEMOVE) {
        cout << "Mouse moving over the window - position ( " << x << " , " << y << " )\n";
    } else if (event == EVENT_MBUTTONDOWN) {
        cout << "Middle button of the mouse is clicked\n";
    } else if (event == EVENT_LBUTTONDOWN) {
        cout << "Left button of the mouse is clicked\n";
    } else if (event == EVENT_RBUTTONDOWN) {
        cout << "Right button of the mouse is clicked\n";
    }
}

// Callback function using keys
void callback_function_keys(int event, int x, int y, int flag, void* userdata) {
    if(flag == (EVENT_FLAG_CTRLKEY + EVENT_FLAG_LBUTTON))
        cout << "Left mouse button is clicked while pressing CTRL key\n";
    else if (flag == (EVENT_FLAG_RBUTTON + EVENT_FLAG_SHIFTKEY)) {
        cout << "Right mouse button is clicked while pressing SHITF key\n";
    } else if (flag == (EVENT_MOUSEMOVE && flag == EVENT_FLAG_ALTKEY)) {
        cout << "Mouse is moved over the window while pressing ALT key - position (" << x << ", " << y << ")" << endl;
    }
}

// Extracting color information at a pixel location in a image
void color_information(int event, int x, int y, int flag, void* userdata) {
    Mat* rgb = (Mat*) userdata; // Converting userData void pointer to mat pointer


    if(event == CV_EVENT_LBUTTONDOWN) { // Left button of the mouse
        int r = (int)(*rgb).at<Vec3b>(y,x)[2];
        int g = (int)(*rgb).at<Vec3b>(y,x)[1];
        int b = (int)(*rgb).at<Vec3b>(y,x)[0];
        cout << x << " " << y << ": " << "(" << r << ", " << g << ", " << b << ")" << endl;
    }
}

/*
    void setMouseCallback(const string& winname, MouseCallback onMouse, void* userdata = 0)
    This function sets a callback function to be called every time any mouse events occurs in the specified window. Here is the detailed explanation of the each parameters of the above OpenCV function.

        winname - Name of the OpenCV window. All mouse events related to this window will be registered
        onMouse - Name of the callback function. Whenever mouse events related to the above window occur, this callback function will be called. This function should have the signature like the following
            void FunctionName(int event, int x, int y, int flags, void* userdata)
                event - Type of the mouse event. These are the entire list of mouse events
                    EVENT_MOUSEMOVE
                    EVENT_LBUTTONDOWN
                    EVENT_RBUTTONDOWN
                    EVENT_MBUTTONDOWN
                    EVENT_LBUTTONUP
                    EVENT_RBUTTONUP
                    EVENT_MBUTTONUP
                    EVENT_LBUTTONDBLCLK
                    EVENT_RBUTTONDBLCLK
                    EVENT_MBUTTONDBLCLK
                x - x coordinate of the mouse event
                y - y coordinate of the mouse event
                flags - Specific condition whenever a mouse event occurs. See the next OpenCV example code for the usage of this parameter. Here is the entire list of enum values which will be possesed by "flags"
                    EVENT_FLAG_LBUTTON
                    EVENT_FLAG_RBUTTON
                    EVENT_FLAG_MBUTTON
                    EVENT_FLAG_CTRLKEY
                    EVENT_FLAG_SHIFTKEY
                    EVENT_FLAG_ALTKEY
                userdata - Any pointer passes to the "setMouseCallback" function as the 3rd parameter (see below)
        userdata - This pointer will be passed to the callback function

*/


int main()
{
    Mat image = imread("horse1.jpg",CV_LOAD_IMAGE_COLOR);

    namedWindow("Horse GUI", WINDOW_FREERATIO);

    resizeWindow("Horse GUI", Size(500,500));

    moveWindow("Horse GUI", 500, 100);

    int slideValue1 = 50;
    createTrackbar("Brightness", "Horse GUI", &slideValue1, 100);
    int slideValue2 = 50;
    createTrackbar("Contrast", "Horse GUI", &slideValue2, 100);

    // Will set the callback function for any mouse movement
    // When needed to pass a data, we must pass the image, frame, and so on

    // setMouseCallback("Horse GUI", color_information, &image);

    while(true) {
        Mat dst;
        int rBrightness = slideValue1 - 50;
        int rContrast = slideValue2 / 50.0;
        image.convertTo(dst, -1, rContrast, rBrightness);
        imshow("Horse GUI", dst);

        if(waitKey(0) >= 0)
            break;
    }


    return 0;
}
