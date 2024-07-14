cmake_minimum_required(VERSION 3.5.0)
cmake_policy( SET CMP0167 NEW)

project(gajed VERSION 0.1.0 LANGUAGES C CXX)
find_package( OpenCV COMPONENTS core highgui )

find_package( Catch2 REQUIRED )

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

set( GENERATE_RAW_IMAGE_SRC src/generate_image.cpp )

set( IMAGE_HEADERS include/image.h )
set( IMAGE_SRC src/image.cpp )

set( ENCODE_JPEG_SRC src/jpeg_encode.cpp )
set( DECODE_JPEG_SRC src/jpeg_decode.c )
set( TEST_SRC tests/tests.cpp )

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )
include_directories( ${Boost_INCLUDE_DIRS} )
link_directories( ${CMAKE_BINARY_DIR}/bin )

add_executable( generate_raw_image ${GENERATE_RAW_IMAGE_SRC} )
add_executable( encode_jpeg ${ENCODE_JPEG_SRC} )
add_executable( tests ${TEST_SRC} ${IMAGE_SRC} )

target_link_libraries( tests Catch2::Catch2 )

target_link_libraries( generate_raw_image ${OpenCV_LIBS} ${Boost_LIBRARIES} )

include(CTest)
include(Catch)
catch_discover_tests(tests)
enable_testing()

