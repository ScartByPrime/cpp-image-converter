cmake_minimum_required(VERSION 3.11)
project(ImgLib CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Политика для target_link_libraries
cmake_policy(SET CMP0079 NEW)

# Обязательный поиск JPEG
find_package(JPEG REQUIRED)
message(STATUS "JPEG found: ${JPEG_LIBRARIES}")
message(STATUS "JPEG include dirs: ${JPEG_INCLUDE_DIRS}")

set(IMGLIB_SOURCES
    img_lib.cpp
    ppm_image.cpp
    jpeg_image.cpp
    bmp_image.cpp
)

set(IMGLIB_HEADERS
    img_lib.h
    ppm_image.h
    jpeg_image.h
    bmp_image.h
    pack_defines.h
)

# Проверяем, не создан ли уже таргет
if(NOT TARGET ImgLib)
    add_library(ImgLib STATIC ${IMGLIB_SOURCES} ${IMGLIB_HEADERS})
    
    target_include_directories(ImgLib PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${JPEG_INCLUDE_DIRS}
    )
    
    target_link_libraries(ImgLib PRIVATE ${JPEG_LIBRARIES})
    
    # Явно указываем, что нужен JPEG
    target_compile_definitions(ImgLib PUBLIC HAS_JPEG_SUPPORT)
else()
    message(STATUS "Target ImgLib already exists, skipping creation")
endif()