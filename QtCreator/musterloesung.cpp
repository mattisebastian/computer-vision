//Eric Neumann
//  D = sqrt([r-r']Â²+[g-g']Â²+[b-b']Â²) < Dmax

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>

using namespace cv;
using namespace std;

int edgeThresh = 1;
int dmax = 20;
Mat image, gray, edge, cedge, taskMat;
int xbase, ybase;

// colors a complete area around a pixel (parameter index) white or red, depending on second parameter and returns its size in pixels
int mark_area(int index, bool red = false) {
    // counts the pixels of the current area
    int count = 1;
    // a simple queue with pixels we need to check for expanding the area
    vector<int> q;

    uint i = 0;
    q.push_back(index);
    // pixel iterator over the resulting image
    Vec3b* ptr = (Vec3b*)taskMat.data;
    uchar testcolor = 1, bval = 255, gval = 255 ;

    // if the area has to be marked red
    if (red) {
        // the area is now previously white, so we have to check for a 255 in the g value instead of 1
        testcolor = 255;
        // we want the white pixel to become red, so we have to set the b and g values to 0
        bval = 0;
        gval = 0;
        // do it for the first pixel
        (*(ptr + q[i]))[0] = 0;
        (*(ptr + q[i]))[1] = 0;
    }
    else
        // make the g value of the base pixel 255, so the pixel is white afterwards
        (*(ptr + q[i]))[1] = 255;

    // now check the for sourounding pixels of the current pixel if they are in the same area and have not been added to the queue
    // break if we handled all elements in the queue -> we found all pixels belonging to the current area
    // there is no actual pop for the queue, we just move an index along the vector, and if it surpases the end -> we break
    while (i < q.size()) {
        // if a pixel needs to be added to the queue, increase the size counter and set the color values to make it white or red

        // the pixel to the right
        if (q[i] % taskMat.cols < taskMat.cols - 1 && (*(ptr + q[i] + 1))[1] == testcolor) {
            (*(ptr + q[i] + 1))[0] = bval;
            (*(ptr + q[i] + 1))[1] = gval;
            count++;
            q.push_back(q[i] + 1);
        }
        // the pixel below
        if (q[i] < taskMat.cols * (taskMat.rows - 1) && (*(ptr + q[i] + taskMat.cols))[1] == testcolor) {
            (*(ptr + q[i] + taskMat.cols))[0] = bval;
            (*(ptr + q[i] + taskMat.cols))[1] = gval;
            count++;
            q.push_back(q[i] + taskMat.cols);
        }
        // the pixel to the left
        if (q[i] % taskMat.cols != 0 && (*(ptr + q[i] - 1))[1] == testcolor) {
            (*(ptr + q[i] - 1))[0] = bval;
            (*(ptr + q[i] - 1))[1] = gval;
            count++;
            q.push_back(q[i] - 1);
        }
        // the pixel above
        if (q[i] >= taskMat.cols && (*(ptr + q[i] - taskMat.cols))[1] == testcolor) {
            (*(ptr + q[i] - taskMat.cols))[0] = bval;
            (*(ptr + q[i] - taskMat.cols))[1] = gval;
            count++;
            q.push_back(q[i] - taskMat.cols);
        }
        i++;
    }
    // return the size of the current area
    return count;
}

// colors the biggest area red, all others white
void colorWhiteRed() {
    int size = taskMat.cols * taskMat.rows;
    int maxsize = 0, maxindex = 0, index = 0, cursize = 0;
    // iterate over every pixel, if its not black and not white, its a not yet handled area
    for (Vec3b* ptr = (Vec3b*)taskMat.data; ptr < (Vec3b*)taskMat.data + size; ptr++, index++) {
        if ((*ptr)[0] == 255 && (*ptr)[1] != 255) {
            // calculate the size of the new found area and color it white, so non of its pixels can trigger this if clause again
            cursize = mark_area(index);
            // if its bigger than any area before, remember its size and its base pixel index
            if (cursize > maxsize) {
                maxsize = cursize;
                maxindex = index;
            }
        }
    }
    // after the maximum area has been found, color it red
    mark_area(maxindex, true);
}

// Builds the basic black and white image regarding D = sqrt([r-r']Â²+[g-g']Â²+[b-b']Â²) < Dmax and calls the function for the red coloring
void calcBlackWhiteRed() {
    // get the bgr colors of the clicked pixel
    Vec3b tempvec = image.at<cv::Vec3b>(ybase, xbase);
    uchar bbase = tempvec.val[0];
    uchar gbase = tempvec.val[1];
    uchar rbase = tempvec.val[2];

    uchar b, g, r;
    // pointer to the data of the resulting image
    Vec3b* ptr2 = (Vec3b*)taskMat.data;

    int size = image.cols * image.rows;

    // use a pointer to iterate over all pixels of the original image - using a pointer should be faster than the Mat.at<type>() function
    for (Vec3b* ptr = (Vec3b*)image.data; ptr < (Vec3b*)image.data + size; ptr++, ptr2++) {
        // get the bgr values of the current pixel
        b = (*ptr).val[0];
        g = (*ptr).val[1];
        r = (*ptr).val[2];
        // if its close enough to the original pixel, color the same pixel in the resulting image, otherwise make it black
        if ((float)sqrt((bbase - b)*(bbase - b) + (gbase - g)*(gbase - g) + (rbase - r)*(rbase - r)) < (float)dmax) {
            (*ptr2).val[0] = 255;
            // make one pixel neither 0 nor 255 to make the size checking of the different areas easier (next step), that step will then make the pixel really white or red
            (*ptr2).val[1] = 1;
            (*ptr2).val[2] = 255;
        }
        else {
            // color pixel black
            (*ptr2).val[0] = 0;
            (*ptr2).val[1] = 0;
            (*ptr2).val[2] = 0;
        }
    }
    // Now the biggest area has to be marked red
    colorWhiteRed();
    // show the final black/white/red image
    imshow("result map", taskMat);
}

// define a trackbar callback - if Dmax is changed via trackbar -> start the calculation
static void onTrackbar(int, void*)
{
    calcBlackWhiteRed();
}

// sets xbase and ybase, so that the color can be aquired in the calcBlackWhiteRed() function, and starts the calculation with the current Dmax value
void mouseHandler(int event, int x, int y, int flags, void* param)
{
    switch(event){
    case CV_EVENT_LBUTTONDOWN:
        xbase = x;
        ybase = y;
        calcBlackWhiteRed();
        break;
    }
}


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

int main( int argc, const char** argv )
{
    help();

    CommandLineParser parser(argc, argv, keys);
    string filename = parser.get<string>("1");

    image = imread(filename);
    if(image.empty())
    {
        printf("Cannot read image file: %s\n", filename.c_str());
        help();
        return -1;
    }
    cedge.create(image.size(), image.type());
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // Create two windows - base map shows orignal image - result map shows the black/white/red image
    namedWindow("base map", 1);
    imshow("base map", image);
    namedWindow("result map", 1);

    // contains the black/white/red image
    taskMat = Mat::zeros(image.size(), CV_8UC3);

    // mouse handler -> handles the click event, writes the coordinates in variables xbase and ybase
    int mouseParam= CV_EVENT_FLAG_LBUTTON;
    cvSetMouseCallback("base map",mouseHandler,&mouseParam);

    // create a toolbar -> for setting the Dmax value
    createTrackbar("Dmax", "base map", &dmax, 100, onTrackbar);

    // Show the image
    onTrackbar(0, 0);

    // Wait for a key stroke; the same function arranges events processing
    waitKey(0);

    return 0;
}
