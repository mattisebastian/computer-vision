#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>

using namespace cv;
using namespace std;

// trying out guided filter implemented in open cv

Mat image, output;

int d;




static void onTrackbar(int, void*)
{
     bilateralFilter(image, output, 4, d, d);
     imshow("result map", output);
}

const char* keys =
{
    "{1| |fruits.jpg|input image name}"
};

int main( int argc, const char** argv )
{

    CommandLineParser parser(argc, argv, keys);
    string filename = parser.get<string>("1");

    image = imread(filename);
    if(image.empty())
    {
        printf("Cannot read image file: %s\n", filename.c_str());
        return -1;
    }

    // apply the OpenCV guided filter

    // create a window that shows the input
    //namedWindow("input");
    //imshow("input", image);

    // create a window for the result
    //namedWindow("result map");
    //imshow("result map", image);

    createTrackbar("BilateralFilter", "result map", &d, 200, onTrackbar);

    waitKey(0);

    return 0;

}
