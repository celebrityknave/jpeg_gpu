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
    // assuming image is 32 x 32 x 8
    Img img = Img();
    REQUIRE( img.getSize() == 8192 );
}