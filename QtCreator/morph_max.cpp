
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>
#include <iostream>
#include <set>

using namespace cv;
using namespace std;

int filter;
Mat dst, src;
int DMax = 20;


static void help()
{
}

const char* keys =
{
    "{1| |fruits.jpg|input image name}"
};

/*
 *
 * Handles the border values
 *
 */

int reflect(int max, int point)
{
    if(point < 0)
    {
        return -point -1;
    }
    else if(point >= max)
    {
        return 2*max - point -1;
    }
    return point;
}


int circular(int max, int point)
{
    if(point < 0)
    {
        return point + max;
    }
    else if(point >= max)
    {
        return point - max;
    }
    return point;
}

static void morph_max()
{

    cout << "morph_max called" << endl;
    // border method: leave out border

    multiset<int> ordered;
    int rows = src.cols, cols = src.rows, x1 = 0, y1 = 0;


    for(int channel = 0; channel <= src.channels(); channel++)
    {
        for(int x = 1; x < rows-1; ++x)
        {
            for(int y = 1; y < cols-1; ++y)
            {
                // make sure the local set is empty before we start
                ordered.clear();

                // put colors of 3x3 box in the set

                for(int xx = x - 1; xx <= x + 1; xx++)
                {
                    for(int yy = y - 1; yy <= y + 1; yy++)
                    {
                        // handle the border values
                        x1 = reflect(cols, xx);
                        y1 = circular(rows, yy);
                        ordered.insert(src.at<Vec3b>(yy, xx)[channel]);

                    }
                }
                // write max into destination pixel

                std::multiset<int>::iterator last = ordered.end();
                last--;
                dst.at<Vec3b>(y, x)[channel] = *last;

            }
        }
    }
    imshow("input", dst);
    cout << "done." << endl;
}


static void onTrackbar(int, void*)
{
    if(!filter)
        imshow( "input", src );
    else
        morph_max();
}


int main( int argc, char** argv )
{
    char* filename = argc >= 2 ? argv[1] : (char*)"fruits.jpg";
    src = imread(filename, 1);

    if( src.empty() )
    {
        cout << "input empty. Usage: ffilldemo <input_name>\n";
        return 0;
    }
    if (src.channels() != 3) {
        cerr << "only works for 3-channel Mat!" << endl;
    }

    help();
    // Save the image on disk
    //imwrite("../output_inputs/Gray_inputNEU.jpg", resultimage);

    // clone src to dst
    dst = src.clone();

    // Show the image
    namedWindow( "input" );
    imshow("input", src);

    createTrackbar("Filter on/off", "input", &filter, 1, onTrackbar);

    cout << "Press ESC to exit.\n";

    while (true){
        int c = waitKey(200);	// loop interval = 0.2 sec.

        if ((char)c == 27){		// Press ESC to exit the program
            break;
        }
    }
    return 0;

}
