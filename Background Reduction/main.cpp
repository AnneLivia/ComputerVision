#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
    Information taken from: https://docs.opencv.org/3.3.0/db/d5c/tutorial_py_bg_subtraction.html
    Background subtraction is a major preprocessing
    steps in many vision based applications.
    For example, consider the cases like visitor
    counter where a static camera takes the number
    of visitors entering or leaving the room, or a
    traffic camera extracting information about the
    vehicles etc. In all these cases, first you need
    to extract the person or vehicles alone.
    Technically, you need to extract the moving
    foreground from static background.
*/

int main()
{
    VideoCapture cap = VideoCapture("people-walking.mp4");

    Mat frame;

    // First the background object must be created using the function createBackGroundSubtractorMOG().
    /*
        Creates mixture-of-gaussian background subtractor
        Ptr<BackgroundSubtractorMOG> createBackgroundSubtractorMOG(int history=200, int nmixtures=5, double backgroundRatio=0.7, double noiseSigma=0)

        history – Length of the history.
        nmixtures – Number of Gaussian mixtures.
        backgroundRatio – Background ratio.
        noiseSigma – Noise strength (standard deviation of the brightness or each color channel). 0 means some automatic value.
    */

    /*

        Creates MOG2 Background Subtractor
        Ptr<BackgroundSubtractorMOG2> createBackgroundSubtractorMOG2(int history=500, double varThreshold=16, bool detectShadows=true )
        history – Length of the history.
        varThreshold – Threshold on the squared Mahalanobis distance between the pixel and the model to decide whether a pixel is well described by the background model. This parameter does not affect the background update.
        detectShadows – If true, the algorithm will detect shadows and mark them. It decreases the speed a bit, so if you do not need this feature, set the parameter to false.

        It provides better adaptibility to varying scenes due illumination changes etc.

    */

    Ptr<BackgroundSubtractorMOG2> foregroundBackground = createBackgroundSubtractorMOG2();

    while(1) {

        cap.read(frame);

        /*
            Now BackgroundSubtractorMOG must be applied

            *** Computes a foreground mask.

            void BackgroundSubtractor::apply(InputArray image, OutputArray fgmask, double learningRate=-1)

            image – Next video frame.
            fgmask – The output foreground mask as an 8-bit binary image.
            learningRate – The value between 0 and 1 that indicates how fast the background model is learnt. Negative parameter value makes the algorithm to use some automatically chosen learning rate. 0 means that the background model is not updated at all, 1 means that the background model is completely reinitialized from the last frame.
        */

        Mat foregroundBackgroundMask;

        foregroundBackground->apply(frame, foregroundBackgroundMask);

        imshow("Frame", frame);
        imshow("FB Mask", foregroundBackgroundMask);

        if(waitKey(30) >= 0)
            break;
    }
    return 0;
}
