#include <stdio.h>
#include <stdlib.h>
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
        //case 'i':
        //    arguments->input_file = arg;
        //    break;
        //case 'o':
        //    arguments->output_file = arg;
        //    break;
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

int read_img( char *filename, char *raw_img )
{
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
#if DEBUG
    fprintf(stdout, "INFILE = %s\nOUTFILE = %s\nVERBOSE = %s\nSILENT = %s\n",
            arguments.args[0], arguments.args[1], 
            arguments.verbose ? "yes" : "no",
            arguments.silent ? "yes" : "no");

#endif
    return 0;
}
