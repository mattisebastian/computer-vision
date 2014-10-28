
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>

using namespace cv;
using namespace std;

int edgeThresh = 1;
Mat inputimage;

// define a trackbar callback
//static void onTrackbar(int, void*)
//{
//    blur(gray, edge, Size(3,3));

//    // Run the edge detector on grayscale
//    Canny(edge, edge, edgeThresh, edgeThresh*3, 3);
//    cedge = Scalar::all(0);

//    image.copyTo(cedge, edge);
//    imshow("Edge map", cedge);
//}

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

void simcolor(Mat& myImage, Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U); // accept only uchar image

    Result.create(myImage.size(), myImage.channels());
    const int nChannels = myImage.channels();

    // use filter2D here!



}

int main( int argc, const char** argv )
{
    help();

    CommandLineParser parser(argc, argv, keys);
    string imageName = parser.get<string>("1");

    inputimage = imread(imageName, 1);
    if(inputimage.empty())
    {
        printf("Cannot read image file: %s\n", imageName.c_str());
        help();
        return -1;
    }

    Mat resultimage;

    simcolor(inputimage, resultimage);

    // Save the image on disk
    imwrite("../output_images/Gray_imageNEU.jpg", resultimage);

    // Show the image
    namedWindow( imageName, CV_WINDOW_AUTOSIZE );
    namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

    imshow( imageName, inputimage );
    imshow( "Gray image", resultimage );



    // Wait for a key stroke; the same function arranges events processing
    waitKey(0);

}


