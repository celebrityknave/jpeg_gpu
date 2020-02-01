/* 
 * This program is just for testing the main encoder program. For the moment, it uses OpenCV to decode
 * inputted image files and outputs raw image files in a user-defined format.
 */
// TODO: - Implement a command line parser
//       - Don't display image when decoding
//       - Add header and associated class
//       - Add functionality to write .RAW files
//       - Add functionality to write .jpg files

#include <iostream>
#include <fstream>
//#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/version.hpp>

#define DEBUG 1

void read_image( std::string filename, cv::Mat &image )
{
    image = cv::imread(filename, cv::IMREAD_UNCHANGED);
    if(! image.data)
    {
        fprintf(stdout, "Could not open image");
        return;
    }
}

void generate_image(std::string filename, cv::Mat &image)
{
    return;
}

void write_image(std::string filename, cv::Mat &image)
{
    //std::cout << filename.substr(filename.length() - 3) << std::endl;
    if(filename.substr(filename.length() - 3) == "raw")
    {
        std::cout << "Saving raw matrix output" << std::endl;
        cv::FileStorage file(filename, cv::FileStorage::WRITE);
        file << "image" << image;

    }
    else
        cv::imwrite(filename, image);
}

int main( int argc, char** argv )
{
    cv::Mat image;
    std::string input_file;
    std::string output_file;

    boost::program_options::options_description desc("Usage");
    desc.add_options()
        // Add command line options here
        ("help,h", "show this menu")
        ("generate,g","Generate image")
        ("read,r","Read raw image")
        ("input,i", boost::program_options::value< std::string >(&input_file), "Input file")
        ("output,o", boost::program_options::value< std::string >(&output_file), "Output file")
        ("display,d","Display image")
    ;

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if(vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }
    // FIXME change to whatever value argv[1] is when I implement a proper command line parser

    if(vm.count("read"))
    {
        read_image(input_file, image);
#if DEBUG
        std::cout << "Input file: " << input_file << std::endl;
        std::cout << "output file: " << output_file << std::endl;
        std::cout << "Image size: " << image.cols << ", " << image.rows << std::endl;
#endif
    }
    else if(vm.count("generate"))
    {
        generate_image(input_file, image);
    }

    write_image(output_file, image);
    if(vm.count("display"))
    {
        cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE );
        cv::imshow("Display window", image);
        cv::waitKey(0);
    }

    return 0;
}
