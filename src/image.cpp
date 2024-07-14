#include <image.h>

Img::Img()
{
    height = 0;
    width = 0;
    bitDepth = 0;
    channels = 0;
}

Img::~Img()
{}

int Img::getColourSpace()
{
    return 0;
}

int Img::getHeight()
{
    return height;
}

int Img::getWidth()
{
    return width;
}

int Img::getSize()
{
    return height * width * bitDepth * channels;
}

int Img::getBitDepth()
{
    return bitDepth;
}

int Img::getNumChannels()
{
    return channels;
}

int Img::encodeJPEG()
{
    return 0;
}