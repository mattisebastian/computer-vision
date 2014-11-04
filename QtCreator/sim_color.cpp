
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int edgeThresh = 1;
Mat input, output;
int DMax = 50;


static void help()
{
    printf("\nThis is an exercise with the goal to find similarly \
           colored regions\n"
                            "Call:\n"
                            "    /.edge [image_name -- Default is fruits.jpg]\n\n");
}

const char* keys =
{
    "{1| |fruits.jpg|input image name}"
};

void simcolor(Mat& myImage, Point seed, Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U); // accept only uchar image

    // find similar colored regions
    // set DMax via trackbar
    int DMax = 50;

    cout << seed << "\n";

    //         << "G: " << intensity.val[1]
    //         << "R: " << intensity.val[2] << endl;



    Result.create(myImage.size(), myImage.channels());
    //const int nChannels = myImage.channels();

    // use filter2D here!


}

static void onMouse( int event, int x, int y, int, void* )
{
    if( event != CV_EVENT_LBUTTONDOWN )
        return;

    Point seed = Point(x,y);

    Vec3b selectioncolor = input.at<Vec3b>(seed.y, seed.x);
    uchar bclick = selectioncolor[0];
    int bc = static_cast<int>(bclick);
    uchar gclick = selectioncolor[1];
    int gc = static_cast<int>(gclick);
    uchar rclick = selectioncolor[2];
    int rc = static_cast<int>(rclick);

    vector<Vec3b> simregions;

    // traverse over full input
    for (int y = 0; y < input.rows; ++y )
    {
        // const float* row_ptr = input.ptr<float>(y);
        for (int x = 0; x < input.cols; ++x)
        {
              Vec3b tempcolor = input.at<Vec3b>(y, x);

              // check for color range
              int bi = static_cast<int>(tempcolor[0]);
              int gi = static_cast<int>(tempcolor[1]);
              int ri = static_cast<int>(tempcolor[2]);


              float D = sqrt(pow(bc - bi, 2) + pow(gc - gi, 2) + pow(rc - ri, 2));


              if(D < DMax)
              {
                  simregions.push_back(tempcolor);
              }

        }
    }

    cout << "B: " << static_cast<int>(selectioncolor[0]) << endl;

    for( vector<Vec3b>::const_iterator i = simregions.begin(); i != simregions.end(); ++i)
        cout << *i << ' ';

    // check if seed is inside the input
    // simcolor(input, seed, resultinput);

}




int main( int argc, char** argv )
{
    char* filename = argc >= 2 ? argv[1] : (char*)"fruits.jpg";
    input = imread(filename, 1);

    if( input.empty() )
    {
        cout << "input empty. Usage: ffilldemo <input_name>\n";
        return 0;
    }
    if (input.channels() != 3) {
        cerr << "only works for 3-channel Mat!" << endl;
    }


    help();



    // Save the image on disk
    //imwrite("../output_inputs/Gray_inputNEU.jpg", resultimage);

    // Show the image
    namedWindow( "input", CV_WINDOW_AUTOSIZE );
    //namedWindow( "Gray input", CV_WINDOW_AUTOSIZE );

    setMouseCallback( "input", onMouse, 0 );

    imshow( "input", input );


    // Wait for a key stroke; the same function arranges events processing
    waitKey(0);
    return 0;

}
