cmake_minimum_required(VERSION 3.11)
project(ImageConverter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_CONVERTER "Build image converter executable" ON)

add_subdirectory(ImgLib)

if(BUILD_CONVERTER)
    add_subdirectory(ImgConverter)
endif()