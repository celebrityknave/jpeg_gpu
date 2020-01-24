cmake_minimum_required(VERSION 2.8)
PROJECT (GPU_JPEG_ENCODER)
find_package(OpenCV REQUIRED)

set( NAME_SRC
    src/generate_raw_image.cpp
)

set( NAME_HEADERS
    include/jpeg_encode.h
)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( ${CMAKE_BINARY_DIR}/bin )
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable( generate_raw_image ${NAME_SRC} ${NAME_HEADERS} )
target_link_libraries( generate_raw_image ${OpenCV_LIBS})


