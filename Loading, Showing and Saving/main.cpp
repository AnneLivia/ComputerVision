#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    // Images are stores in MAT variables
    // Imread is the function used to read an image, this function receives the
    // file address of the image, and a flag where:
    // CV_LOAD_IMAGE_ANYDEPTH: If set, return 16-bit/32-bit image when the input has the corresponding depth, otherwise convert it to 8-bit.
    // CV_LOAD_IMAGE_COLOR - If set, always convert image to the color one
    // CV_LOAD_IMAGE_GRAYSCALE - If set, always convert image to the grayscale one
    // CV_LOAD_IMAGE_UNCHANGED (<0) loads the image as is (including the alpha channel if present)
    // If the second argument is not specified, it is implied CV_LOAD_IMAGE_COLOR

    Mat photocolor = imread("horse1.jpg", CV_LOAD_IMAGE_COLOR);
    Mat photogray = imread("horse1.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    // so we create an OpenCV window using the namedWindow function
    // WINDOW_AUTOSIZE is the only supported one if you do not use the Qt backend. In this case the window size will take up the size of
    // the image it shows. No resize permitted!
    // WINDOW_NORMAL on Qt you may use this to allow window resize. The image will resize itself according to the current window size. By using the | operator you also need to specify if you would like the image to
    // keep its aspect ratio (WINDOW_KEEPRATIO) or not (WINDOW_FREERATIO).
    // If the second argument is not specified by the user, it is implied to be WINDOW_AUTOSIZE

    /*

        CV_WINDOW_NORMAL or CV_WINDOW_AUTOSIZE: CV_WINDOW_NORMAL enables you to resize the window, whereas CV_WINDOW_AUTOSIZE adjusts automatically the window size to fit the displayed image (see imshow() ), and you cannot change the window size manually.
        CV_WINDOW_FREERATIO or CV_WINDOW_KEEPRATIO: CV_WINDOW_FREERATIO adjusts the image with no respect to its ratio, whereas CV_WINDOW_KEEPRATIO keeps the image ratio.
        CV_GUI_NORMAL or CV_GUI_EXPANDED: CV_GUI_NORMAL is the old way to draw the window without statusbar and toolbar, whereas CV_GUI_EXPANDED is a new enhanced GUI.
        namedWindow("Name of the Window",CV_WINDOW_AUTOSIZE); // Automatically sizes the windows and don't allow the user to adjusts it
        namedWindow("Name of the Window",CV_WINDOW_FREERATIOn); // the user can adjusts it

    */

    namedWindow("Color",WINDOW_AUTOSIZE);
    //namedWindow("Color",WINDOW_FREERATIO);
    namedWindow("Fixed",WINDOW_AUTOSIZE);

    // Finally, to update the content of the OpenCV window with a new image use the imshow function. Specify the OpenCV window name to
    // update and the image to use during this operation

    imshow("Color",photocolor);
    imshow("Fixed",photogray);

    // Resizes window to the specified size
    // void resizeWindow(const String& winname, int width, int height)

    /* Parameters:
        WinName = Window name
        width = The new window width
        height = The new window height
    */

    // photocolor.cols = number of cols, photocolor.rows = number of rows

    //resizeWindow("Color",photocolor.cols/2, photocolor.rows/2);
    //resizeWindow("Fixed",photocolor.cols/2, photocolor.rows/2);

    // MoveWindow - Moves window to the specified position
    // void moveWindow(const String& winname, int x, int y)

    /* Parameters:
        WinName = Window name
        x = The new x-coordinate of the window
        y = The new y-coordinate of the window
    */

    moveWindow("Color",20,100);
    moveWindow("Fixed",20 + photogray.cols + 5,100);

    // Because we want our window to be displayed until the user presses a key (otherwise the program would end far too quickly), we use the waitKey function whose only parameter is just how long should it wait for a user input
    // (measured in milliseconds). Zero means to wait forever.

    waitKey(0);

    // imwrite("outputGray.jpg",photogray); // Easiest way to save a file

    return 0;
}


