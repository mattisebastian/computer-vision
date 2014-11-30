#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <string>
#include <set>
#include <stdlib.h>
#define n(x,y,channel) newImage.at<Vec3b>(x,y)[channel]
#define i(x,y,channel) img.at<Vec3b>(x,y)[channel]



using namespace cv;
using namespace std;

static void help()
{
    cout << "This is a fast median filtering program. Just load an image and drag \n"
            "the trackbar to apply fast median filtering. :-) \n"
            "Press Escape to quit the program." << endl;
}

Mat img;
Mat newImage;
int medianIterations=0;
int debug=0;
//declare 2 multisets
std::multiset<int> higher, lower;



static void onTrackbar(int, void*);


int main( int argc, char** argv )
{
    //read the image
    char* filename = argc >= 2 ? argv[1] : (char*)"fruits.jpg";
    Mat img0 = imread(filename, -1);
    if(img0.empty())
    {
        cout << "Couldn't open the image " << filename << ". Make sure fruits.jpg is in the same folder as the compiled program or "
             "append an image as parameter. \n" << endl;
        return 0;
    }

    help();

    namedWindow( "image", 1 );

    img = img0.clone();
    //show the original image
    imshow("image", img);
    createTrackbar("Filter enabled", "image", &medianIterations, 1, onTrackbar);

    for(;;)
    {
        //wait for a user input
        char c = (char)waitKey();


        //escape
        if( c == 27 )
            break;
        }


    return 0;
}



static void addPixel(int desiredPixelColor, int comparePixelColor)
{
    if(desiredPixelColor>=comparePixelColor)
    {
        higher.insert(desiredPixelColor);
    }
    else lower.insert((desiredPixelColor));
}

static void balanceMultiSets()
{
    while((int)(lower.size()-higher.size())>=2)
    {
        //get a pointer to the largest value of lower
        std::multiset<int>::iterator value= lower.end();
        value--;
        higher.insert(*value);
        lower.erase(value);
    }
    while((int)(higher.size()-lower.size())>=2)
    {
        //get a pointer to the smallest value of higher
        std::multiset<int>::iterator value= higher.begin();
        lower.insert(*value);
        higher.erase(value);
    }
}

static void killOldPixels(int x, int y, int channel)
{
    for(int tempx=x-1; tempx<=x+1; tempx++)
    {
        //search in lower multiset for value
        std::multiset<int>::iterator old=lower.find(i(tempx,y-2,channel));
        //if not found, search in higher multiset and delete it there
        if(old==lower.end())
        {
            old=higher.find(i(tempx,y-2,channel));
            //delete the value
            higher.erase(old);
        }
        else //delete the value
        lower.erase(old);
    }
}

static void onTrackbar(int, void*) {

    //if no filtering should be done, simply show the image
    if(medianIterations==0)
    {
        imshow("image", img);
    }
    else{

        newImage=img.clone();
        for(int channel=0; channel<=img.channels(); channel++)
        {
                for (int x=1; x<img.rows-1; x++)
                {
                   //make sure all multisets are completely empty before working on a new row
                   higher.clear();
                   lower.clear();
                   for(int y=1; y<img.cols-1; y++)
                   {
                           if(y==1)
                           {
                               int compare = n(x,y,channel);
                               //sort all pixels within the 3x3 box into the right multiset (higher or lower)
                               //this is only done once for each row
                               for(int boxx=x-1; boxx<=x+1; boxx++)
                               {
                                   for(int boxy=y-1; boxy<=y+1; boxy++)
                                   {
                                       addPixel(i(boxx,boxy,channel),compare);
                                   }
                               }
                               balanceMultiSets();
                           }
                           else
                           {
                                    //get the comparision pixel
                                    std::multiset<int>::iterator value = lower.end();
                                    value--;
                                    int compare = *value;
                                    //kill old pixels (the ones which fall out of the box on the left)
                                    killOldPixels(x, y, channel);
                                    //add new pixels (the right ones) to the multiset
                                    addPixel(i(x-1,y+1,channel), compare);
                                    addPixel(i(x,y+1,channel), compare);
                                    addPixel(i(x+1,y+1,channel), compare);
                                    balanceMultiSets();

                           }
                           //returns an iterator pointing to one element beyond the last one
                           std::multiset<int>::iterator value = lower.end();
                           value--;
                           //decrease the pointer in order to point to the last element of the multiset
                           //write color value into pixel
                           n(x,y,channel) = *value;
                       }
                       }

                    }

                imshow("image", newImage);
                }
}


