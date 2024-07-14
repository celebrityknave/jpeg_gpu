cmake_minimum_required(VERSION 3.5.0)
project(jpeg_gpu_decoder VERSION 0.1.0 LANGUAGES C CXX)
find_package( OpenCV COMPONENTS core highgui )
find_package( Boost COMPONENTS program_options REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Set boost parameters
set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME OFF )

set( GENERATE_RAW_IMAGE_SRC src/generate_image.cpp )
#set( GENERATE_RAW_IMAGE_HEADERS include/jpeg_encode.h )

set( ENCODE_JPEG_SRC src/jpeg_encode.c )
set( DECODE_JPEG_SRC src/jpeg_decode.c )

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )
include_directories( ${Boost_INCLUDE_DIRS} )
link_directories( ${CMAKE_BINARY_DIR}/bin )

add_executable( generate_raw_image ${GENERATE_RAW_IMAGE_SRC} )
add_executable( encode_jpeg ${ENCODE_JPEG_SRC} )
target_link_libraries( generate_raw_image ${OpenCV_LIBS} ${Boost_LIBRARIES} )

include(CTest)
enable_testing()

