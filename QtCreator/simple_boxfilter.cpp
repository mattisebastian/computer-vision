
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"

//#include <stdio.h>
//#include <iostream>

//using namespace cv;
//using namespace std;

//int edgeThresh = 1;
//Mat dst, src;
//int DMax = 20;


//static void help()
//{
//}

//const char* keys =
//{
//    "{1| |fruits.jpg|input image name}"
//};

//void boxfilter()
//{
//    cout << "boxfilter called" << endl;
//    //Vec3b* ptr = (Vec3b*) src.data;

//    // border method: leave out border
//    int rows = src.cols;
//    int cols = src.rows;

//    // pointer based approach, test later
//    //    for(Vec3b* ptr = (Vec3b*) src.data; ptr < (Vec3b*) src.data + size; ptr++, index++)
//    //    {
//    //    }
//    for(int x = 1; x < rows-1; ++x)
//    {
//        for(int y = 1; y < cols-1; ++y)
//        {
//            // get average of 3x3 box
//            Vec3f sum(0, 0, 0);

//            for(int xx = x - 1; xx < x + 2; xx++)
//            {
//                for(int yy = y - 1; yy < y + 2; yy++)
//                {
//                    sum += (Vec3f) src.at<Vec3b>(yy, xx);
//              //      cout << "adding to sum: " << src.at<Vec3b>(yy, xx) << endl;
//                }
//            }
//            // write average into destination pixel
//            Vec3f average = sum / 9;
//            src.at<Vec3b>(y, x) = (Vec3b) average;
//            //cout << "sum: " << sum << average << " at: " << x << "," << y << endl;
//        }
//    }
//    imshow("output", src);
//}


//int main( int argc, char** argv )
//{
//    char* filename = argc >= 2 ? argv[1] : (char*)"fruits.jpg";
//    src = imread(filename, 1);

//    if( src.empty() )
//    {
//        cout << "input empty. Usage: ffilldemo <input_name>\n";
//        return 0;
//    }
//    if (src.channels() != 3) {
//        cerr << "only works for 3-channel Mat!" << endl;
//    }


//    help();



//    // Save the image on disk
//    //imwrite("../output_inputs/Gray_inputNEU.jpg", resultimage);

//    // Show the image
//    namedWindow( "input" );
//    namedWindow( "output" );
//    imshow( "input", src );
//    boxfilter();
//    //imshow("output", dst);

//    // Wait for a key stroke; the same function arranges events processing
//    waitKey(0);
//    return 0;

//}
