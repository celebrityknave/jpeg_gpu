#include <stdio.h>
#include <string.h>
#include <argp.h>

class Img
{
public:
    Img(int height, int width, int bitDepth, int channels);
    ~Img();
    // Returns enum value based on colour type. BGR, RGB, grayscale, etc.
    int getColourSpace();
    // Returns height of output JPEG image in pixels
    int getHeight();
    // Returns width of output JPEG image in pixels
    int getWidth();
    // Returns size of output JPEG image in bytes
    int getSize();
    // Returns image bit-depth
    int getBitDepth();
    // Returns number of colour channels
    int getNumChannels();
    // Returns error code based on success of JPEG encode
    int encodeJPEG();

private:
    int height;
    int width;
    int bitDepth;
    int size;
    int channels;
};