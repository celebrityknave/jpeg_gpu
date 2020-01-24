/* This program is just for testing the main encoder program. It uses OpenCV to decode inputted image files and
 * outputs raw image files in a user-defined format
 */

#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main( int argc, char** argv)
{
    if(argc != 2)
    {
        fprintf(stdout, "Usage: \n");
        return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1], cv::IMREAD_UNCHANGED);
    if(! image.data)
    {
        fprintf(stdout, "Could not open image");
        return -1;
    }

    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE );
    cv::imshow("Display window", image);

    cv::waitKey(0);
    return 0;
}

    

