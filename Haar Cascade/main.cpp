#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

/*
    What is haar cascade?
    Haar Cascade is a classifier which is used to detect the object
    for which it has been trained for, from a source.

    The haar cascade is done by superimposing the positive image over a set of negative images.
    Negative image is basically an image which does not contain the object for which the haar cascade is being made for.
    And the positive image is the object in which the haar cascade will detect.

    There are predefined haar cascades on:
     https://github.com/opencv/opencv/tree/master/data/haarcascades
     https://github.com/Itseez/opencv/tree/master/data/haarcascades

    It is a machine learning based approach where a cascade function is trained from
    a lot of positive and negative images. It is then used to detect objects in other images.
*/

int main()
{
    // In this project will be done face and eye recognition using:
    // Face: https://github.com/Itseez/opencv/blob/master/data/haarcascades/haarcascade_frontalface_default.xml
    // Eye: https://github.com/Itseez/opencv/blob/master/data/haarcascades/haarcascade_eye.xml
    // Smile: https://raw.githubusercontent.com/opencv/opencv/master/data/haarcascades/haarcascade_smile.xml

    CascadeClassifier face_cascade = CascadeClassifier("haar_cascade/haarcascade_frontalface_default.xml"); // Loading xml for frontal face
    CascadeClassifier eye_cascade = CascadeClassifier("haar_cascade/haarcascade_eye.xml"); // Haar cascade file for eye
    CascadeClassifier smile_cascade = CascadeClassifier("haar_cascade/haarcascade_smile.xml");
    if(face_cascade.empty() || eye_cascade.empty() || smile_cascade.empty()) {
        cout << "Error, loading cascade\n";
        exit(-1);
    }
    // Loading the web cam
    VideoCapture cap(0);

    Mat img; // Mat object to use

    while(true) {

        cap.read(img); // Passing frames from the video to img object

        // Converting to gray
        Mat gray;
        cvtColor(img, gray, CV_BGR2GRAY);

        /*
            Now it's going to be used the function to detect objects of different sizes in the input image (img)
            the detected objects are returned in this function as a list of rectangles
            So there's must be a vector<Rect>& objects to receive it;
            CascadeClassifier::detectMultiScale(const Mat& image, vector<Rect>& objects, double scaleFactor=1.1, int minNeighbors=3, int flags=0, Size minSize=Size(), Size maxSize=Size())

            Parameters of this method are:

            cascade – Haar classifier cascade (OpenCV 1.x API only). It can be loaded from XML or YAML file using Load(). When the cascade is not needed anymore, release it using cvReleaseHaarClassifierCascade(&cascade).
            image – Matrix of the type CV_8U containing an image where objects are detected. // Gray scale image
            objects – Vector of rectangles where each rectangle contains the detected object.
            scaleFactor – Parameter specifying how much the image size is reduced at each image scale.
            minNeighbors – Parameter specifying how many neighbors each candidate rectangle should have to retain it.
            flags – Parameter with the same meaning for an old cascade as in the function cvHaarDetectObjects. It is not used for a new cascade.
            minSize – Minimum possible object size. Objects smaller than that are ignored.
            maxSize – Maximum possible object size. Objects larger than that are ignored.

        */

        vector<Rect>faces; // Vector to store all rect founded for face.
        vector<Rect>eyes; // Vector to store all rect founded for eyes
        vector<Rect>smiles; // Vector to store all rect founded for smiles
        face_cascade.detectMultiScale(gray, faces, 1.3, 5);

        // Now will be drawn a rectangle on the faces detected
        for(auto faceRect : faces) {
            rectangle(img, Point(faceRect.x, faceRect.y), Point(faceRect.x + faceRect.width, faceRect.y + faceRect.height), Scalar(0,255,0), 2, LINE_AA);

            // For each face, will be detect eyes
            Mat faceROI_gray = gray(faceRect); // Getting a ROI (Region of interest) of the face, to now detect the eye (Gray Scale)
            Mat faceROI_color = img(faceRect); // Getting a ROI (Region of interest) of the face, to now use this region to draw the rectangle of the eyes

            // Now use the detectMultiScale method to find the eyes and in case it finds, store in a vector of rectangles
            eye_cascade.detectMultiScale(faceROI_gray, eyes, 1.3, 5);

            // If eyes were found
            for(auto eyeRect : eyes) {
                rectangle(faceROI_color, Point(eyeRect.x, eyeRect.y), Point(eyeRect.x + eyeRect.width, eyeRect.y + eyeRect.height), Scalar(255,0,0), 2, LINE_AA);
            }

            // Also detect Smiles in the face region
            //smile_cascade.detectMultiScale(faceROI_gray, smiles, 2.5, 20);

            // if smile were found
            //for(auto smileRect : smiles) {
              //  rectangle(faceROI_color, Point(smileRect.x, smileRect.y), Point(smileRect.x + smileRect.width, smileRect.y + smileRect.height), Scalar(0,255,255), 2, LINE_AA);
            //}
        }

        imshow("Frame", img);

        if(waitKey(1) >= 0) // Tap any key to stop
            break;
    }
    return 0;
}
