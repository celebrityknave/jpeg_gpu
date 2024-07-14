/* 
 * This program is just for testing the main encoder program. For the moment,
 * it uses OpenCV to decode inputted image files and outputs image files of a
 * number of different formats.
 */
// TODO: 
//       - Add header and associated class
//       - Improve command parsing so that the read or generate flags can only be
//       chosen by themselves
//       - Add option to generate images:
//          - Gaussian noise
//          - Random noise
//          - Tiled image
//          - Image with text
//          - Image with geometric shapes

#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <argp.h>

#define DEBUG 1

const char *argp_program_bug_address = "<evan.peter.blake@gmail.com>";
const char *argp_program_version = "CAJE 0.0.0";
static char doc[] = "CAJE -- CUDA-accelerated JPEG encoder";
static char args_doc[] = "INFILE, OUTFILE";

struct Arguments
{
    bool verbose;
    bool quiet;
    bool silent;
    bool display;
    bool gaussian;
    std::string output_file;
};

static struct argp_option options[] = {
    // name         key     arg        flags           doc
    {"verbose",     'v',    0,          0,              "Produce verbose output." },
    {"quiet",       'q',    0,          0,              "Don't produce any output." },
    {"gaussian",    'g',    0,          0,              "Generate Gaussian noise."},
    {"output",      'o',    "OUTFILE",  0,              "Location of output file" },
    {"display",     'd',    0,          0,              "Whether to display the image after generation"},
    { 0 }
};

static error_t
parse_opt(int key, char* arg, struct argp_state* state)
{
    error_t err = 0;
    struct Arguments *arguments = (struct Arguments*)(state->input);

    switch(key)
    {
        case ARGP_KEY_INIT:
            break;
        case 'q':
            arguments->silent = 1;
            break;
        case 'v':
            arguments->verbose = 1;
            break;
        case ARGP_KEY_ARG:
            // FIXME : this won't work. Using the argp_key_arg case is an artefact of the previous method of arg parsing
            if(state->arg_num >= 2)
                argp_usage(state);
            arguments->output_file = arg;
            break;
        case ARGP_KEY_END: // Not enough arguments
            if(state->arg_num < 2)
                argp_usage(state);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

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
    if(filename.substr(filename.length() - 3) == "raw")
    {
        std::cout << "Saving raw matrix output" << std::endl;
        cv::FileStorage file(filename, cv::FileStorage::WRITE);
        // TODO: I don't like this syntax being used when it's done differently
        // everywhere else in the code. Fix this.
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

    struct Arguments arguments;
    arguments.silent = 0;
    arguments.verbose = 0;
    arguments.output_file = "-";

    argp_parse(&argp, argc, argv, 0,0, &arguments);

    // FIXME change to whatever value argv[1] is when I implement a proper command line parser

    if(arguments.gaussian)
    {
        generate_image(input_file, image);
    }

    write_image(output_file, image);
    if(arguments.display)
    {
        cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE );
        cv::imshow("Display window", image);
        cv::waitKey(0);
    }

    return 0;
}
