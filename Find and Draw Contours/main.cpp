#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Function to use in the createMouseCallback to check the HSV values from some specific pixel
void mouse(int event, int x, int y, int flag, void *para) {
    if(event == CV_EVENT_LBUTTONDOWN) {
        Mat *rgb = (Mat *)para;
        int r = (*rgb).at<Vec3b>(x,y)[2];
        int g = (*rgb).at<Vec3b>(x,y)[1];
        int b = (*rgb).at<Vec3b>(x,y)[0];
        Mat hsv, color;
        color = Mat(Size(1,1), CV_8UC3, Scalar(r,g,b));
        cvtColor(color, hsv, CV_BGR2HSV);
        cout << hsv << endl;
    }
}

int main()
{
    // Opening the default camera
    VideoCapture cap(0);
    Mat frame;

    // Loop to run the video
    while(true) {
        // Reading each frame from the default camera
        cap.read(frame);

        // Blurring image to remove noise
        Mat blurImage;
        GaussianBlur(frame, blurImage, Size(5,5), 0.5);

        // converting image from RGB to HSV
        Mat frameHSV;
        cvtColor(blurImage, frameHSV, CV_BGR2HSV);

        // Find upper and lower limits for the red color
        Scalar lowerb = Scalar(110,100,100);
        Scalar upperb = Scalar(179,255,255);

        // Creating the mask according to those parameters
        Mat mask;
        inRange(frameHSV, lowerb, upperb, mask);

        // Creating a kernel to apply two morphology operations, Opening and closing.
        Mat kernel = Mat::ones(3,3, CV_8UC1);
        morphologyEx(mask, mask, MORPH_CLOSE, kernel);
        morphologyEx(mask, mask, MORPH_OPEN, kernel);

        // Apply contours on the mask
        /*
            Contours can be explained simply as a curve joining all the continuous
            points (along the boundary), having same color or intensity. The contours
            are a useful tool for shape analysis and object detection and recognition.
            For better accuracy, use binary images. So before finding contours, apply threshold or canny edge detection.
            In OpenCV, finding contours is like finding white object from black background. So remember, object to be
            found should be white and background should be black.
            For more information, check out OpenCV documentation.

            void findCountours(InputOutputArray image, OutputArrayOfArrays contours, OutputArray hierarchy, int mode, int method, Point offset = Point());
            This function finds contours in a binary image using the algorithm from Satoshi Suzuki and others. Topological structural analysis of digitized
            binary images by border following. Computer Vision, Graphics, and Image Processing, 30(1):32–46, 1985.

            Where the parameters are:
            Image = input image, of an 8-bit single channel, where the image is treated as binary, so non-zero pixels are treated as 1.
            Contours = detected contours, each contour is store as a vector of points (e.g. vector<vector<Point> >).
            Hierarchy = Optional output vector (e.g. std::vector<cv::Vec4i>), containing information about the image topology.
            It has as many elements as the number of contours.
            Mode = mode of the Contour retrieval algorithm, where:
                RETR_EXTERNAL: retrieves only the extreme outer contours.
                RETR_LIST: retrieves all of the contours without establishing any hierarchical relationships.
                RETR_CCOMP:retrieves all of the contours and organizes them into a two-level hierarchy. At the top level, there are external boundaries of the components.
                At the second level, there are boundaries of the holes. If there is another contour inside a hole of a connected component, it is still put at the top level.
                RETR_TREE: retrieves all of the contours and reconstructs a full hierarchy of nested contours.
                RETR_FLOODFILL: ?
            Method: the contour approximation algorithm, where:
                CHAIN_APPROX_NONE: stores absolutely all the contour points. That is, any 2 subsequent points (x1,y1) and (x2,y2) of the contour will be either horizontal, vertical or diagonal neighbors, that is, max(abs(x1-x2),abs(y2-y1))==1.
                CHAIN_APPROX_SIMPLE: compresses horizontal, vertical, and diagonal segments and leaves only their end points. For example, an up-right rectangular contour is encoded with 4 points.
                CHAIN_APPROX_TC89_L1: applies one of the flavors of the Teh-Chin chain approximation algorithm [168]
                CHAIN_APPROX_TC89_KCOS: applies one of the flavors of the Teh-Chin chain approximation algorithm [168]
                [168] C-H Teh and Roland T. Chin. On the detection of dominant points on digital curves. Pattern Analysis and Machine Intelligence, IEEE Transactions on, 11(8):859–872, 1989.
            offset: Optional offset by which every contour point is shifted. This is useful if the contours are extracted from the image ROI and then they should be analyzed in the whole image context.
        */
        // The contours will be store in the bellow vector
        vector<vector<Point> > contours;

        // Find contours
        findContours(mask, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

        // Subtracting the background from the foreground with bitwise_and
        Mat result;
        bitwise_and(frame, frame, result, mask = mask);

        /*
            To draw the contours, cv2.drawContours function is used. It can also be used to draw any shape provided you have its boundary points
            void drawContours(InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness=1, int lineType=8, InputArray hierarchy=noArray(), int maxLevel=INT_MAX, Point offset=Point() )
            Where:
            image = Destination image.
            contours = All the input contours. Each contour is stored as a point vector.
            contourIdx = Parameter indicating a contour to draw. If it is negative, all the contours are drawn.
            color = Color of the contours.
            thickness = Thickness of lines the contours are drawn with. If it is negative (for example, thickness=CV_FILLED ), the contour interiors are drawn.
            lineType = Line connectivity. See line() for details.
            hierarchy = Optional information about hierarchy. It is only needed if you want to draw only some of the contours (see maxLevel ).
            maxLevel = Maximal level for drawn contours. If it is 0, only the specified contour is drawn. If it is 1, the function draws the contour(s) and all the nested contours. If it is 2, the function draws the contours, all the nested contours, all the nested-to-nested contours, and so on. This parameter is only taken into account when there is hierarchy available.
            offset = Optional contour shift parameter. Shift all the drawn contours by the specified offset = (dx , dy).
            contour = Pointer to the first contour.
            external_color = Color of external contours.
            hole_color = Color of internal contours (holes).
            the function draws contour outlines in the image if thickness >= 0 or fills the area bounded by the contours if thickness < 0
            For more information, checkout OpenCV documentation.
        */

        // In order to drawn only the one with the bigger area.
        // The function contourArea is used to calculate the area.

        // running through all contours
        for(int i = 0; i < (int)contours.size(); i++) {
            if(contourArea(contours[i]) > 600)
                drawContours(frame, contours, -1, Scalar(0,255,0), 2, LINE_AA);
        }

        // Drawing contours, -1 is used it's going to be drawn every contours
        // drawContours(result, contours, -1, Scalar(0,255,0), 2, 8);

        // Showing images
        imshow("Frame", frame);
        imshow("Mask", mask);
        imshow("Result", result);

        // While any key is pressed, the loop will continue running
        if(waitKey(1) >= 0)
            break;
    }
    return 0;
}
