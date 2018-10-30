#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat image = imread("horse1.jpg", CV_LOAD_IMAGE_COLOR);
    /*
        Scaling is just resizing the image.
        OpenCV comes with a function cv.resize() for this purpose.
        The size of the image can be specified manually, or you
        can specify the scaling factor. Different interpolation
        methods are used. Preferable interpolation methods are
        cv.INTER_AREA for shrinking and cv.INTER_CUBIC (slow) &
        cv.INTER_LINEAR for zooming.

        cv.resize (src, dst, dsize, fx = 0, fy = 0, interpolation = cv.INTER_LINEAR)

        src	- input image
        dst	- output image; it has the size dsize (when it is non-zero) or the size computed from src.size(), fx, and fy; the type of dst is the same as of src.
        dsize - output image size; if it equals zero, it is computed as:
        Either dsize or both fx and fy must be non-zero.

        fx	- scale factor along the horizontal axis; when it equals 0, it is computed as
        (double)dsize.width/src.cols

        fy	- scale factor along the vertical axis; when it equals 0, it is computed as
        (double)dsize.height/src.rows

        In the mathematical field of numerical analysis, interpolation is a method of constructing new data points within the range of a discrete set of known data points.

        Image interpolation occurs when you resize or distort your image from one pixel grid to another. Image resizing is necessary when you need to increase or decrease the total number of pixels, whereas remapping can occur when you are correcting for lens distortion or rotating an image. Zooming refers to increase the quantity of pixels, so that when you zoom an image, you will see more detail.



        INTER_NEAREST - a nearest-neighbor interpolation
        INTER_LINEAR - a bilinear interpolation (used by default)
        INTER_AREA - resampling using pixel area relation. It may be a preferred method for image decimation, as it gives moire’-free results. But when the image is zoomed, it is similar to the INTER_NEAREST method.
        INTER_CUBIC - a bicubic interpolation over 4x4 pixel neighborhood
        INTER_LANCZOS4 - a Lanczos interpolation over 8x8 pixel neighborhood

    */

    Mat scaled_img;
    cv::resize(image, scaled_img, Size(), 0.5, 0.5);

    /*
        Translation:
        Translation is the shifting of object's location. If you know the shift in (x,y) direction, let it be (tx,ty), you can create the transformation matrix M as follows:
        M = [ 1 0 tx ]
            [ 0 1 ty ]

        We use the function: cv.warpAffine (src, dst, M, dsize, flags = cv.INTER_LINEAR, borderMode = cv.BORDER_CONSTANT, borderValue = new cv.Scalar())

        src – input image.
        dst – output image that has the size dsize and the same type as src .
        M – 2\times 3 transformation matrix.
        dsize – size of the output image.
        flags – combination of interpolation methods (see resize() ) and the optional flag WARP_INVERSE_MAP that means that M is the inverse transformation ( \texttt{dst}\rightarrow\texttt{src} ).
        borderMode – pixel extrapolation method (see borderInterpolate()); when borderMode=BORDER_TRANSPARENT , it means that the pixels in the destination image corresponding to the “outliers” in the source image are not modified by the function.
        borderValue – value used in case of a constant border; by default, it is 0.

        The function warpAffine transforms the source image using the specified matrix:

        dst(x,y) = src(m11x + m12y + m13, m21x + m22y + m23)

    */

    Mat translation_image;

    // size of the image
    int width = image.cols;
    int height = image.rows;

    Mat matrix = (Mat_<double>(2,3) << 1, 0, 100, 0, 1, -30);

    warpAffine(image, translation_image,matrix,Size(width, height));

    /*
        Rotate image: Rotation of an image for an angle theta is achieved by the transformation matrix of the form
        M = [ cos theta - sin theta ]
            [ sin theta  cos theta  ]

        But OpenCV provides scaled rotation with adjustable center of rotation so that you can rotate at any location you prefer. Modified transformation matrix is given by

        [ alpha beta (1 - alpha) . center . x  - beta . center . y ]
        [ -beta alpha beta . center . x + ( 1 - alpha) . center . y]

        where: alpha = scale . cos theta
               beta = scale . sin theta

        We use the function: getRotationMatrix2D (center, angle, scale)
        center	- center of the rotation in the source image.
        angle	- rotation angle in degrees. Positive values mean counter-clockwise rotation (the coordinate origin is assumed to be the top-left corner).
        scale	- isotropic scale factor.

    */

    Mat rotated_image;
    Mat matr = getRotationMatrix2D(Point(width / 2, width / 2), 90, 1);

    warpAffine(image, rotated_image, matr, Size(width, height));
    imshow("Image", image);
    imshow("Scaled Image", scaled_img);
    imshow("Translated Image", translation_image);
    imshow("Rotated Image", rotated_image);


    waitKey();
    return 0;
}
