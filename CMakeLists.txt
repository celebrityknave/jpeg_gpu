cmake_minimum_required(VERSION 2.8)
project ( GPU_JPEG_ENCODER )
find_package( OpenCV COMPONENTS core highgui )
find_package( Boost COMPONENTS program_options REQUIRED)

# Set boost parameters
set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME OFF )

set( GENERATE_RAW_IMAGE_SRC src/generate_raw_image.cpp )
#set( GENERATE_RAW_IMAGE_HEADERS include/jpeg_encode.h )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )
include_directories( ${Boost_INCLUDE_DIRS} )
link_directories( ${CMAKE_BINARY_DIR}/bin )

add_executable( generate_raw_image ${GENERATE_RAW_IMAGE_SRC} )
target_link_libraries( generate_raw_image ${OpenCV_LIBS} ${Boost_LIBRARIES} )


