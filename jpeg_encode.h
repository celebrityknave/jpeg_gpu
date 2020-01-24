#include <stdio.h>

// Returns enum value based on colour type. BGR, RGB, grayscale, etc.
int getColour();
// Returns height of output JPEG image in pixels
int getHeight();
// Returns width of output JPEG image in pixels
int getWidth();
// Returns size of output JPEG image in bytes
int getSize();
// Returns error code based on success of JPEG encode
int encodeJPEG();

