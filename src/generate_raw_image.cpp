/* This program is just for testing the main encoder program. It uses OpenCV to decode inputted image files and
 * outputs raw image files in a user-defined format
 */

#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.cpp>

void read_image( int argc, char** argv)
{
    if(argc != 2)
    {
        fprintf(stdout, "Usage: \n");
        return;
    }

    cv::Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR); // FIXME : Change this to the 'Unchanged' option (Need to look up what it is called)
    if(! image.data)
    {
        fprintf(stdout, "Could not open image");
        return;
    }

    cv::namedWindow("Display window", WINDOW_AUTOSIZE );
    cv::imshow("Display window", image);

    cv::waitKey(0);
    return;
}

    

