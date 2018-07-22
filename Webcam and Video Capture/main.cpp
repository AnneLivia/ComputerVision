#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int fps = 20; // frames por second

int main()
{
    Mat frame; // Will store frames

    // Class for video capturing from video files, image sequences or cameras. The class provides C++ API for capturing video from cameras or for reading video files and image sequences. Here is how the class can be used:

    // You can select the second camera by passing 1 and so on. After that, you can capture frame-by-frame. But at the end, don’t forget to release the capture.

    VideoCapture vid(0); // open the default camera

    if(!vid.isOpened()) // Check if succeeded
        return -1;

    // vid >> frame; // other option to read

    while(vid.read(frame)) { // while it can read information it will run
        imshow("Webcam",frame);
        // the waitkey will wait for at least 1000/fps milliseconds
        if(waitKey(1000/fps) >= 0) // waitkey return an integer value according to what the user presses on the screen
            break;
    }

    // the camera will be deinitialized automatically in VideoCapture destructor

    return 1; // Return 1 for success
}
