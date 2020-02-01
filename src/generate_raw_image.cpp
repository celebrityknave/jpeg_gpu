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

void read_image( std::string filename, cv::Mat &image )
{
    image = cv::imread(filename, cv::IMREAD_UNCHANGED);
    if(! image.data)
    {
        fprintf(stdout, "Could not open image");
        return;
    }

    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE );
    cv::imshow("Display window", image);

    cv::waitKey(0);

}

void generate_image(std::string filename, cv::Mat &image)
{
    return;
}

void write_image(std::string filename, cv::Mat &image)
{
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
        std::cout << "Input file: " << input_file << std::endl;
        read_image(input_file, image);
        std::cout << "Image size: " << image.cols << ", " << image.rows << std::endl;
    }
    if(vm.count("generate"))
    {
        generate_image(input_file, image);
    }
    write_image(output_file, image);

    return 0;
}
