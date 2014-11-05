
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int edgeThresh = 1;
Mat input, output;
int DMax = 20;


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

    Result.create(myImage.size(), myImage.channels());



}

static void onMouse( int event, int row, int col, int, void* )
{
    if( event != CV_EVENT_LBUTTONDOWN )
        return;
    // the point where the user clicked
    Point seed = Point(row, col);

    // the color of the point where the user clicked
    Vec3b selectioncolor = input.at<Vec3b>(seed.y, seed.x);

    int bc = static_cast<int>(selectioncolor[0]);
    int gc = static_cast<int>(selectioncolor[1]);
    int rc = static_cast<int>(selectioncolor[2]);

    // vector of points where the color difference is less than DMax
    vector<Point> simregions;

    //    // traverse over full input image
    for (int y = 0; y < input.rows; ++y )
    {

        for (int x = 0; x < input.cols; ++x)
        {
            // the color of the pixel currently looked at
            Vec3b tempcolor = input.at<Vec3b>(y, x);

            // check for color range
            int bi = static_cast<int>(tempcolor.val[0]);
            int gi = static_cast<int>(tempcolor.val[1]);
            int ri = static_cast<int>(tempcolor.val[2]);


            float D = sqrt(pow(bc - bi, 2) + pow(gc - gi, 2) + pow(rc - ri, 2));

            if(D < DMax)
            {
                Point matchingPixel = Point(x, y);
                simregions.push_back(matchingPixel);
            }

        }
    }


        for( vector<Point>::iterator i = simregions.begin(); i != simregions.end(); ++i)
        {
    //        // turn all pixle in the result vector white
    ////        cout << "former color: " << input.at<Vec3b>(*i)[0] << endl;
    //        input.at<Vec3b>(*i)[0] = 255;
    ////        cout <<  "now set to: " << input.at<Vec3b>(i->x, i->y)[0] << endl;
    //        input.at<Vec3b>(i->x, i->y)[1] = 255;
    //        input.at<Vec3b>(i->x, i->y)[2] = 255;

            if(i->x < 512 || i->y < 480)
            {
               cout << "schwarzes schaaf: " <<*i << endl;
            }


        }
    cout << input.size() << endl;
    cout << "similar pixels selected: "<< simregions.size() << endl;

    imshow( "input", input );

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
