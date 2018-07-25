#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    /* Point:
       point define 2d points in an image.
       Point pt;
       pt.x = 10;
       pt.y = 8;
       or Point pt = Point(10,8);
       Scalar:
       Represents a 4-element vector. The type Scalar is widely used in OpenCV for passing pixel values.
       It is used extensively to represent BGR color values (3 parameters). It is not necessary to define the last argument if it is not going to be used.
       Scalar( a, b, c ); BGR colors where B = a, G = b and R = c
    */

    // Drawing an atom
    /*
        Types:
        where U is unsigned integer type, S is signed integer type, and F is float type.
        so CV_8UC3 is an 8-bit unsigned integer matrix/image with 3 channels.
        Although it is most common that this means an RGB (or actually BGR) image,
        it does not mandate it. It simply means that there are three channels,
        and how you use them is up to you and your application.
    */

    // Creating a mat atom, full of zeros, of cols 400, rows 400 and type 8UC3, that is, this will store 3 channels
    int wAndH = 400;

    Mat atom = Mat::zeros(wAndH,wAndH,CV_8UC3); // A matrix 400x400 of color black
    Mat lin = Mat::zeros(wAndH,wAndH,CV_8UC3);
    Mat rect = Mat::zeros(wAndH,wAndH,CV_8UC3);
    Mat poly = Mat::zeros(wAndH,wAndH,CV_8UC3);
    Mat polylin = Mat::zeros(wAndH,wAndH,CV_8UC3);
    Mat text = Mat::zeros(wAndH,wAndH,CV_8UC3);
    Mat arrow = Mat::zeros(wAndH,wAndH,CV_8UC3);

    int thickness = 2;
    int linetype = CV_AA;

    /*
        Ellipse:
        Drawing an Ellipse
        void ellipse(Mat& img, Point center, Size axes, double angle, double startAngle, double endAngle, const Scalar& color, int thickness=1, int lineType=8, int shift=0)

    img = Image.
    center = Center of the ellipse.
    axes = Length of the ellipse axes.
    angle = Ellipse rotation angle in degrees.
    startAngle = Starting angle of the elliptic arc in degrees.
    endAngle = Ending angle of the elliptic arc in degrees.
    box = Alternative ellipse representation via RotatedRect or CvBox2D. This means that the function draws an ellipse inscribed in the rotated rectangle.
    color = Ellipse color.
    thickness = Thickness of the ellipse arc outline, if positive. Otherwise, this indicates that a filled ellipse sector is to be drawn.
    lineType = Type of the ellipse boundary.
    shift = Number of fractional bits in the coordinates of the center and values of axes.

    The functions ellipse with less parameters draw an ellipse outline, a filled ellipse, an elliptic arc, or a filled ellipse sector.
    A piecewise-linear curve is used to approximate the elliptic arc boundary.
    If you use the first variant of the function and want to draw the whole ellipse, not an arc, pass startAngle=0 and endAngle=360.

    Type of the line:

    8 (or omitted) - 8-connected line.
    4 - 4-connected line.
    CV_AA - antialiased line.

    Obs: Size(wAndH/3, wAndH/14) - "height and width"
    */

    ellipse(atom, Point(wAndH/2,wAndH/2), Size(wAndH/3, wAndH/14), 90, 0, 360, Scalar(0, 255, 0), thickness, linetype);
    ellipse(atom, Point(wAndH/2,wAndH/2), Size(wAndH/3, wAndH/14), 0, 0, 360, Scalar(0, 0, 255), thickness, linetype);
    ellipse(atom, Point(wAndH/2,wAndH/2), Size(wAndH/3, wAndH/14), 45, 0, 360, Scalar(255, 0, 0), thickness, linetype);
    ellipse(atom, Point(wAndH/2,wAndH/2), Size(wAndH/3, wAndH/14), -45, 0, 360, Scalar(255, 0, 255), thickness, linetype);

    /*
        Circle:
        void circle(Mat& img, Point center, int radius, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
        Par+ameters:

    img = Image where the circle is drawn.
    center = Center of the circle.
    radius = Radius of the circle.
    color = Circle color.
    thickness = Thickness of the circle outline, if positive. Negative thickness means that a filled circle is to be drawn.
    lineType = Type of the circle boundary.
    shift = Number of fractional bits in the coordinates of the center and in the radius value.
    The function circle draws a simple or filled circle with a given center and radius.
    // Thickness
    FILLED = -1; negative number means that the circle, ellipses, etc. will be filled.
    LINE_4  = 4, < 4-connected line
    LINE_8  = 8, < 8-connected line
    LINE_AA = 16 < antialiased line
    */

    circle(atom,Point(wAndH/2,wAndH/2),wAndH/34,Scalar(0,0,255), FILLED, LINE_8);
    circle(atom,Point(wAndH/2,wAndH/2),wAndH/20,Scalar(255,0,0), 2, LINE_8);

    /*
        Line:
        Draws a line segment connecting two points.
        void line(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)

        img - Image.
        pt1 - First point of the line segment.
        pt2 - Second point of the line segment.
        color - Line color.
        thickness - Line thickness.
        lineType - Type of the line:
        8 (or omitted) - 8 - connected line.
        4 - 4 - connected line.
        CV_AA - antialiased line.
        shift - Number of fractional bits in the point coordinates.
    */
    line(lin,Point(wAndH/2,wAndH/2),Point(wAndH/5,-wAndH/5),Scalar(110,220,0),8, CV_AA);

    /*
        Rectangle:
        Draws a simple, thick, or filled up-right rectangle.
        C++: void rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
        C++: void rectangle(Mat& img, Rect rec, const Scalar& color, int thickness=1, int lineType=8, int shift=0 )

        Parameter:

        img = Image.
        pt1 = Vertex of the rectangle.
        pt2 = Vertex of the rectangle opposite to pt1 .
        rec = Alternative specification of the drawn rectangle.
        color = Rectangle color or brightness (gray scale image).
        thickness = Thickness of lines that make up the rectangle. Negative values, like CV_FILLED , mean that the function has to draw a filled rectangle.
        lineType = Type of the line. See the line() description.
        shift = Number of fractional bits in the point coordinates.

    */

    rectangle(rect,Point(wAndH/2,wAndH/4),Point(wAndH/10,wAndH/10),Scalar(0,0,255),8,CV_AA);
    rectangle(rect,Point(wAndH/2,wAndH/4),Point(wAndH/10,wAndH/10),Scalar(255,0,0),FILLED,CV_AA);

    /*
        Drawing filled polygon: Fills the area bounded by one or more polygons.
        void fillPoly(Mat& img, const Point** pts, const int* npts, int ncontours, const Scalar& color, int lineType=8, int shift=0, Point offset=Point() )
        Parameters:
        img - Image.
        pts - Array of polygons where each polygon is represented as an array of points.
        npts - Array of polygon vertex counters.
        ncontours - Number of contours that bind the filled region.
        color - Polygon color.
        lineType - Type of the polygon boundaries. See the line() description.
        shift - Number of fractional bits in the vertex coordinates.
        offset - Optional offset of all points of the contours.
        The function fillPoly fills an area bounded by several polygonal contours.
        The function can fill complex areas, for example, areas with holes, contours with self-intersections (some of their parts), and so forth.
    */

   // Creating points to use in the function
    Point pt[1][3];
    pt[0][0] = Point(wAndH/2,wAndH/2);
    pt[0][1] = Point(wAndH/2,wAndH);
    pt[0][2] = Point(wAndH/6,wAndH/8);
    const Point* ppt[1] = {pt[0]}; // Point of points

    int npt[] = {3}; // Array of polygon vertex counters.

    fillPoly(poly,ppt,npt,1,Scalar(255,255,255),LINE_8);

    /*
        C++: void polylines(Mat& img, const Point** pts, const int* npts, int ncontours, bool isClosed, const Scalar& color, int thickness=1, int lineType=8, int shift=0 )
        C++: void polylines(InputOutputArray img, InputArrayOfArrays pts, bool isClosed, const Scalar& color, int thickness=1, int lineType=8, int shift=0 )

        img – Image.
        pts – Array of polygonal curves.
        npts – Array of polygon vertex counters.
        ncontours – Number of curves.
        isClosed – Flag indicating whether the drawn polylines are closed or not. If they are closed, the function draws a line from the last vertex of each curve to its first vertex.
        color – Polyline color.
        thickness – Thickness of the polyline edges.
        lineType – Type of the line segments. See the line() description.
        shift – Number of fractional bits in the vertex coordinates.
        The function polylines draws one or more polygonal curves.
    */
    // 258, 250 - center, 28, 480 - bottom left, the other is bottom right
    Point p[1][3] = {Point(258,250), Point(28,480), Point(480,488)};
    const Point* pt2[1] = {p[0]};
    int npt2[] = {3};

    polylines(polylin,pt2,npt2,1,1,Scalar(255,0,0),1,8);

    /*
        Putting text in a image
        PutText = draws a text string
        void putText(Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color, int thickness=1, int lineType=8, bool bottomLeftOrigin=false )

        img = Image.
        text = Text string to be drawn.
        org = Bottom-left corner of the text string in the image.
        fontFace = Font type. One of FONT_HERSHEY_SIMPLEX, FONT_HERSHEY_PLAIN, FONT_HERSHEY_DUPLEX, FONT_HERSHEY_COMPLEX, FONT_HERSHEY_TRIPLEX, FONT_HERSHEY_COMPLEX_SMALL, FONT_HERSHEY_SCRIPT_SIMPLEX, or FONT_HERSHEY_SCRIPT_COMPLEX, where each of the font ID’s can be combined with FONT_HERSHEY_ITALIC to get the slanted letters.
        fontScale = Font scale factor that is multiplied by the font-specific base size.
        color = Text color.
        thickness = Thickness of the lines used to draw a text.
        lineType = Line type. See the line for details.
        bottomLeftOrigin = When true, the image data origin is at the bottom-left corner. Otherwise, it is at the top-left corner.
        The function putText renders the specified text string in the image. Symbols that cannot be rendered using the specified font are replaced by question marks.

    */

    putText(text,"Testing putText()",Point(50,150),FONT_HERSHEY_DUPLEX,1,Scalar(0,255,0),1,CV_AA,true);

    /*
        ArrowedLine: Draws a arrow segment pointing from the first point to the second one.
        void arrowedLine(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int line_type=8, int shift=0, double tipLength=0.1)

    img - Image.
    pt1 - The point the arrow starts from.
    pt2 - The point the arrow points to.
    color - Line color.
    thickness - Line thickness.
    line_type -
    Type of the line:
        8 (or omitted) - 8-connected line.
        4 - 4-connected line.
        CV_AA - antialiased line.
    shift - Number of fractional bits in the point coordinates.
    tipLength - The length of the arrow tip in relation to the arrow length
    he function arrowedLine draws an arrow between pt1 and pt2 points in the image.
    */

    arrowedLine(arrow,Point(wAndH/2,wAndH/2),Point(wAndH/2,wAndH/4),Scalar(0,0,255),1,8,1,0.7);

    imshow("Arrow",arrow);
    imshow("Text",text);
    imshow("Polyline",polylin);
    imshow("Ellipses and Circle",atom);
    imshow("Line",lin);
    imshow("Rectangle",rect);
    imshow("Polygon", poly);

    waitKey();
    return 0;
}
