# Image Converter

A lightweight command-line tool with support for "inconvenient" formats (BMP, PPM) and the ability to convert to and from JPEG with a simple and intuitive interface.

## Features

- **Multi-format support**:
  - JPEG (.jpg, .jpeg) - read/write
  - BMP (.bmp) - read/write
  - PPM (.ppm) - read/write
- **Automatic format detection** based on file extension
- **Simple command-line interface**
- **Static linking** for easy distribution

## Requirements

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.11 or higher
- libjpeg (required for JPEG support)

## Installing libjpeg

**Ubuntu/Debian:**
- *bash*
- sudo apt update
- sudo apt install libjpeg-dev

**Fedora/CentOS/RHEL:**
- *bash*
- sudo dnf install libjpeg-turbo-devel

**macOS (Homebrew):**
- *bash*
- brew install libjpeg-turbo

**Windows (vcpkg):**
- *bash*
- vcpkg install libjpeg-turbo

## Building
 - *bash*
**Clone the repository**
- git clone https://github.com/ScartByPrime/cpp-image-converter
- cd cpp-image-converter

**Create build directory**
- mkdir build && cd build

**Configure with CMake**
- cmake ..

**Build**
- cmake --build .

**The executable will be in build/ImgConverter/**

### Usage example (Linux)
- *bash*
- ./imgconv <input_file.your_extention> <output_file.preferred_extention>
- *The tool automatically detects the format from file extensions.*