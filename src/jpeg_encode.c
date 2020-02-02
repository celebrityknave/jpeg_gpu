#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>

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

struct arguments
{
    char *args[2]; // FIXME maybe more?
    int silent;
    int verbose;
    char *input_file;
    char *output_file;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;

    switch(key)
    {
        case 'q': case 's':
            arguments->silent = 1;
            break;
        case 'v':
            arguments->verbose = 1;
            break;
        case ARGP_KEY_ARG: // Too many arguments
            if(state->arg_num >= 2)
                argp_usage(state);
            arguments->args[state->arg_num] = arg;
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

int getFileExtension(char *filename, char **fileExtension)
{
    *fileExtension = strrchr(filename, '.');
    if(*fileExtension == NULL)
        *fileExtension = "";

    return 0;
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

int readImg( char *filename, char **raw_img )
{
    // Open file
    FILE *raw_img_data;
    fprintf(stdout, "Opening file: %s...\n", filename);
    raw_img_data = fopen( filename, "rb" );
    if( raw_img_data == NULL )
    {
        fprintf(stderr, "Error: Cannot open file\n");
        return 1;
    }


    // Parse file extension
    char *fileExtension;
    getFileExtension(filename, &fileExtension);

    // Process file using different methods depending on file extension
#if DEBUG
    fprintf(stdout, "File extension: %s\n", fileExtension);
#endif
    if(strcmp(fileExtension, ".jpg") == 0)
    {
        fprintf(stdout, "File already in JPEG format\n");
    }
    else if( strcmp(fileExtension, ".bmp") == 0)
    {
        fprintf(stdout, "File in BMP format\n");
        readBMP(raw_img_data, raw_img);
    }
    else if(strcmp(fileExtension, ".png") == 0)
        fprintf(stdout, "File in PNG format\n");
    else if(strcmp(fileExtension, ".tif") == 0)
        fprintf(stdout, "File in TIF format\n");
    else 
        fprintf(stderr, "Error: Unknown file format: %s\n", fileExtension);

    return 0;
}

int main(int argc, char **argv)
{
    struct arguments arguments;
    arguments.silent = 0;
    arguments.verbose = 0;
    arguments.input_file = "-";
    arguments.output_file = "-";

    argp_parse(&argp, argc, argv, 0,0, &arguments);

    char *raw_img;
    int img_quality;
    int img_height;
    int img_width;
    int img_channels;
    int img_bitdepth;

#if DEBUG
    fprintf(stdout, "INFILE = %s\nOUTFILE = %s\nVERBOSE = %s\nSILENT = %s\n",
            arguments.args[0], arguments.args[1], 
            arguments.verbose ? "yes" : "no",
            arguments.silent ? "yes" : "no");

#endif
    readImg( arguments.args[0], &raw_img );

    return 0;

}
