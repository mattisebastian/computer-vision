#include "fast_guided_filter.hpp"

void guided_filter(Mat& inp, Mat& outp)
{
    cvtColor(inp, outp, CV_BGR2GRAY);
}

int main( int argc, char** argv )
{
    input_image = imread("fruits.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file

    if( input_image.empty() )
    {
           cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }



    guided_filter(input_image, output_image);
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", input_image ); // Show our image inside it.
    imshow( "Display window", output_image);
    waitKey(0);                             // Wait for a keystroke in the window
    return 0;
}
