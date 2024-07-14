#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>
#include <string>

#define DEBUG 1

const char *argp_program_bug_address = "<evan.peter.blake@gmail.com>";
const char *argp_program_version = "CAJE 0.0.0";
static char doc[] = "CAJE -- CUDA-accelerated JPEG encoder";
static char args_doc[] = "INFILE, OUTFILE";

static struct argp_option options[] = {
    // name     key  arg        flags           doc
    {"verbose", 'v', 0,         0,              "Produce verbose output." },
    {"quiet",   'q', 0,         0,              "Don't produce any output." },
    {"silent",  's', 0,         OPTION_ALIAS },
    //{"input",   'i', "INFILE",  0,              "Location of input file" },
    //{"output",  'o', "OUTFILE", 0,              "Location of output file" },
    { 0 }
};

struct Arguments
{
    int verbose;
    int quiet;
    int silent;
    //int args[2]; // FIXME maybe more?
    std::string input_file;
    std::string output_file;
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
        case 'q': case 's':
            arguments->silent = 1;
            break;
        case 'v':
            arguments->verbose = 1;
            break;
        case ARGP_KEY_ARG: // Too many arguments
            if(state->arg_num >= 2)
                argp_usage(state);
            arguments->input_file = arg;
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

std::string getFileExtension(const char *filename)
{
    std::string fileExtension = strrchr(filename, '.');

    return fileExtension;
}
int readBMP( FILE *bmp_img_data, char **raw_img )
{

    return 0;
}
int readPNG( FILE *png_img_data, char **raw_img )
{

    return 0;
}
int readTIF( FILE *tif_img_data, char **raw_img )
{

    return 0;
}

int readImg( std::string filename, char **raw_img )
{
    // Open file
    FILE *raw_img_data;
    fprintf(stdout, "Opening file: %s...\n", filename.c_str());
    raw_img_data = fopen( filename.c_str(), "rb" );
    if( raw_img_data == NULL )
    {
        fprintf(stderr, "Error: Cannot open file\n");
        return 1;
    }


    // Parse file extension
    std::string fileExtension = getFileExtension(filename.c_str());

    // Process file using different methods depending on file extension
#if DEBUG
    fprintf(stdout, "File extension: %s\n", fileExtension);
#endif
    if(strcmp(fileExtension.c_str(), ".jpg") == 0)
    {
        fprintf(stdout, "File already in JPEG format\n");
    }
    else if( strcmp(fileExtension.c_str(), ".bmp") == 0)
    {
        fprintf(stdout, "File in BMP format\n");
        readBMP(raw_img_data, raw_img);
    }
    else if(strcmp(fileExtension.c_str(), ".png") == 0)
        fprintf(stdout, "File in PNG format\n");
    else if(strcmp(fileExtension.c_str(), ".tif") == 0)
        fprintf(stdout, "File in TIF format\n");
    else 
        fprintf(stderr, "Error: Unknown file format: %s\n", fileExtension);

    return 0;
}

int main(int argc, char **argv)
{
    struct Arguments arguments;
    arguments.silent = 0;
    arguments.verbose = 0;
    arguments.input_file = "-";
    arguments.output_file = "-";

    argp_parse(&argp, argc, argv, 0,0, &arguments);

    char *raw_img;

#if DEBUG
    fprintf(stdout, "INFILE = %s\nOUTFILE = %s\nVERBOSE = %s\nSILENT = %s\n",
            arguments.input_file, arguments.output_file, 
            arguments.verbose ? "yes" : "no",
            arguments.silent ? "yes" : "no");

#endif
    readImg( arguments.input_file, &raw_img );

    return 0;

}
