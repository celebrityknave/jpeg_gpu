#include <image.hpp>

Img::Img(int m_height, int m_width, int m_bitDepth, int m_channels)
{
    height = m_height;
    width = m_width;
    bitDepth = m_bitDepth;
    channels = m_channels;
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