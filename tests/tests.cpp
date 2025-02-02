#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>


#include <image.hpp>
Img img = Img(32, 32, 8, 3);
TEST_CASE ("Height is returned", "[image]")
{

    REQUIRE( img.getHeight() == 32 );
}

TEST_CASE ("Width is returned", "[image]")
{
    REQUIRE( img.getWidth() == 32 );
}

TEST_CASE ("Image size in bytes is returned", "[image]")
{
    // assuming image is 32 x 32 x 8 x 3
    REQUIRE( img.getSize() == 24576 );
}

TEST_CASE ("Image bit-depth is returned", "[image]")
{
    // assuming 8-bit image depth
    REQUIRE( img.getBitDepth() == 8);
}

TEST_CASE ("Number of image colour channels is returned", "[image]")
{
    // Assuming RGB
    REQUIRE( img.getNumChannels() == 3);
}


#include <huffman_code.h>
TEST_CASE ("Frequency table of string is correctly populated", "[huffman]")
{
    char test_string[] = "I am a test string";
    int table_size;
    data_node* test_node = get_frequency_table(test_string, &table_size);
    data_node* sorted_nodes = sort_nodes_by_freq(test_node, table_size);
    for(int i=0; i < table_size; i++ )
    {
        REQUIRE( sorted_nodes[0].freq == 4);
        REQUIRE( sorted_nodes[1].freq == 3);
        REQUIRE( sorted_nodes[2].freq == 2);
        REQUIRE( sorted_nodes[3].freq == 2);
    }

}