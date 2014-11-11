#ifndef FAST_GUIDED_FILTER_HPP
#define FAST_GUIDED_FILTER_HPP

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>
#include <iostream>


using namespace cv;
using namespace std;

Mat input_image;
Mat output_image;

void guided_filter(Mat& input_img, Mat& output_img);

int main( int argc, char** argv );


#endif // FAST_GUIDED_FILTER_HPP
