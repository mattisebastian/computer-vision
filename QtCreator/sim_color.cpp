
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int edgeThresh = 1;
Mat image0, image;

static void help()
{
    printf("\nThis sample demonstrates Canny edge detection\n"
           "Call:\n"
           "    /.edge [image_name -- Default is fruits.jpg]\n\n");
}

const char* keys =
{
    "{1| |fruits.jpg|input image name}"
};

static void onMouse( int event, int x, int y, int, void* )
{
    if( event != CV_EVENT_LBUTTONDOWN )
        return;

    Point seed = Point(x,y);
    // check if seed is inside the image
    cout << seed << "\n";
    cout << x << ", " << y << " pixel is selected.\n";


}


void simcolor(Mat& myImage, Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U); // accept only uchar image

    Result.create(myImage.size(), myImage.channels());
    //const int nChannels = myImage.channels();

    // use filter2D here!



}

int main( int argc, char** argv )
{
    char* filename = argc >= 2 ? argv[1] : (char*)"fruits.jpg";
    image0 = imread(filename, 1);

    if( image0.empty() )
    {
        cout << "Image empty. Usage: ffilldemo <image_name>\n";
        return 0;
    }
    help();
    image0.copyTo(image);
    Mat resultimage;

    //simcolor(image, resultimage);

    // Save the image on disk
    //imwrite("../output_images/Gray_imageNEU.jpg", resultimage);

    // Show the image
    namedWindow( "image", CV_WINDOW_AUTOSIZE );
    //namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

    setMouseCallback( "image", onMouse, 0 );

    imshow( "image", image );


    // Wait for a key stroke; the same function arranges events processing
    waitKey(0);
    return 0;

}
