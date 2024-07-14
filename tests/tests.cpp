#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <image.h>

TEST_CASE ("Height is returned", "[image]")
{
    Img img = Img();
    REQUIRE( img.getHeight() == 32 );
}

TEST_CASE ("Width is returned", "[image]")
{
    Img img = Img();
    REQUIRE( img.getWidth() == 32 );
}

TEST_CASE ("Image size in bytes is returned", "[image]")
{
    // assuming image is 32 x 32 x 8 x 3
    Img img = Img();
    REQUIRE( img.getSize() == 24576 );
}

TEST_CASE ("Image bit-depth is returned", "[image]")
{
    // assuming 8-bit image depth
    Img img = Img();
    REQUIRE( img.getBitDepth() == 8);
}

TEST_CASE ("Number of image colour channels is returned", "[image]")
{
    // Assuming RGB
    Img img = Img();
    REQUIRE( img.getNumChannels() == 3);
}