// CV aufgabe2.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdlib.h>
#include <set>

#define DEBUG true


using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	if (argc < 2)
	{
		return -1;
	}

	Mat image, output_image;															// input and output images
	int cern_size = 0;
	multiset<int> set;
	int mode = 0;																		// 0:=min; 1:=max; 2:=median;

	image = cvLoadImageM(argv[1], CV_LOAD_IMAGE_COLOR);									// Read the file (imread does not work properly on windows)
	if (argc > 2){
		cern_size = atoi(argv[2]);
	}
	if (argc > 3){
		mode = atoi(argv[3]);
	}
	
	

	if (!image.data)																	// Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	output_image = image.clone();
	
	
	
	int rows = image.rows;
	int cols = image.cols;
	
	int cern_range = cern_size / 2;															// filters even values of cern_size

	for (int channel = 0; channel < 3; channel++){											// one iteration for each color channel
		for (int y = 0; y < rows; y++){
			set.clear();
			for (int i = y-cern_range; i <= y+cern_range; i++){								// fill the Set with the first values at the begin of each row 
				for (int j = 0; j < (cern_range); j++){
					if (i >= 0 && i < rows && j < cols){									// prevent access out of range
						set.insert(image.at<Vec3b>(j, i)[channel]);				 
					}					
				}
			}
			for (int x = 0; x < cols; x++){
				int h_x_left = x - (cern_range+1);
				int h_x_right = x + cern_range;
				for (int i = -cern_range; i <= cern_range; i++){							// remove most left pixels and add pixels at the right border of the cernel
					int h_y = y + i;
					if (h_y >= 0 && h_y < rows && h_x_left >= 0 ){							// prevent access out of range
						set.erase(set.find(image.at<Vec3b>(h_x_left, h_y)[channel]));
					}
					if (h_y >= 0 && h_y < rows && h_x_right < cols){
						set.insert(image.at<Vec3b>(h_x_right, h_y)[channel]);
					}
				}
				// BEGIN actual operation
				// TODO support all three modes
				switch (mode){
				case 1:{
					std::multiset<int>::iterator p_p = set.end();							// get a pointer to the greatest value of the set
					p_p--;
					output_image.at<Vec3b>(x, y)[channel] = (*p_p);
					break;
				}
				case2:{
					
					break;
				}
				default:{

					std::multiset<int>::iterator value = set.begin();						// get a pointer to the smallest value of the set
					output_image.at<Vec3b>(x, y)[channel] = (*value);
				}
				}
				// END actual OPERATION
				
				
			}
			if (false){
				cout << "row " << y << "channel " << channel << " complete \n";
			}
		}
		if (DEBUG){
			cout << "channel " << channel << " complete \n";
		}
	}





	if (DEBUG){
		namedWindow("window", WINDOW_AUTOSIZE);												// Create a window for display.
		imshow("window", output_image);
	}

	//TODO write image to file
	

	cout << "Press ESC to exit.\n";
	while (true){
		int c = waitKey(200);	// loop interval = 0.2 sec.

		if ((char)c == 27){		// Press ESC to exit the program
			break;
		}
	}

	return 0;
}