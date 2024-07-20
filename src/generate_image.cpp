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
const char *argp_program_version = "GAJE 0.0.0";
static char doc[] = "GAJED -- GPU-accelerated JPEG encoder/decode Image generator";
static char args_doc[] = "";

struct Arguments
{
    bool verbose;
    bool quiet;
    bool silent;
    bool display;
    bool gaussian;
    bool noise;
    bool tiled;
    bool text;
    int height;
    int width;
    std::string output_file;
};

static struct argp_option options[] = {
    // name         key     arg        flags           doc
    {"verbose",     'v',    0,          0,              "Produce verbose output." },
    {"quiet",       'q',    0,          0,              "Don't produce any output." },
    {"gaussian",    'g',    0,          0,              "Generate Gaussian noise."},
    {"random",      'u',    0,          0,              "Generate uniform random noise."},
    {"tiled",       't',    0,          0,              "Generate tiled image"},
    {"text",        'w',    "TEXT",     0,              "Annotate image with text"},
    {"output",      'o',    "OUTFILE",  0,              "Location of output file" },
    {"rows",        'r',    "HEIGHT",   0,              "Height of generated image" },
    {"columns",     'c',    "WIDTH",    0,              "Width of generated image"},
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
        case 'g':
            arguments->gaussian = 1;
            break;
        case 'u':
            arguments->noise = 1;
            break;
        case 'd':
            arguments->display = 1;
            break;
        case 'o':
            arguments->output_file = arg;
            break;
        case 'w':
            arguments->text = arg;
            break;
        case 't':
            arguments->tiled = 1;
            break;
        case 'r':
            arguments->height = (int)strtol(arg, NULL, 10);;
            break;
        case 'c':
            arguments->width = (int)strtol(arg, NULL, 10);
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

cv::Mat generate_uniform_random(int height, int width)
{
    // Uniform random
    cv::Mat mat(height, width, CV_8UC1);
    cv::randu(mat, cv::Scalar::all(0), cv::Scalar::all(255));
    return mat;
}

cv::Mat generate_normal_random(int height, int width)
{
    cv::Mat mat(height, width, CV_8UC1);
    // 74 is based on the result of stdev(0:255). This is probably equivalent to uniform random though.
    // Might be worth combining thesee into a single method and making uniform rand a special case.
    cv::randn(mat, cv::Scalar::all(128), cv::Scalar::all(74));
    return mat;
}

cv::Mat generate_tiled(int height, int width, int tileSize)
{
    cv::Mat mat(0, width, CV_8UC1);
    bool x = false;
    int xi = height / tileSize;
    int xj = width / tileSize;
    std::cout << "height/tile: " << xi << "\nwidth/tile: " << xj << std::endl;

    for(int i=0; i < int(height/tileSize); i++)
    {
        cv::Mat vmat(tileSize, 0, CV_8UC1);
        for(int i=0; i < int(width/tileSize); i++)
        {
            cv::Mat umat(tileSize, tileSize, CV_8UC1);
            
            if(x)
            {
                umat = cv::Scalar(0);
            }
            else
            {
                umat = cv::Scalar(255);
            }
            x = !x;
            cv::hconcat(vmat, umat, vmat);
        }
        x = !x;
        cv::vconcat(mat, vmat, mat);

    }
    
    return mat;
}

cv::Mat add_text(cv::Mat mat)
{
    return mat;
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
    {
        cv::imwrite(filename, image);
    }
        
}

int main( int argc, char** argv )
{
    cv::Mat image = cv::Mat::zeros(cv::Size(30,30), CV_8UC1);
    std::string output_file;

    struct Arguments arguments;
    arguments.silent = 0;
    arguments.verbose = 0;

    std::cout << "Parsing args" << std::endl;
    argp_parse(&argp, argc, argv, 0,0, &arguments);
    std::cout << "Finished parsing args" << std::endl;

    // FIXME change to whatever value argv[1] is when I implement a proper command line parser

    if(arguments.gaussian == true)
    {
        image = generate_normal_random(arguments.height, arguments.width);
    }

    if(arguments.noise == true)
    {
        image = generate_uniform_random(arguments.height, arguments.width);
    }

    if(arguments.tiled == true)
    {
        std::cout << "Tiling image" << std::endl;
        image = generate_tiled(arguments.height, arguments.width, 64);
    }


    if(!arguments.output_file.empty())
    {
        write_image(arguments.output_file, image);
    }
    
    if(arguments.display == true)
    {
        std::cout << "Displaying image" << std::endl;
        cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE );
        cv::imshow("Display window", image);
        cv::waitKey(0);
    }

    return 0;
}
