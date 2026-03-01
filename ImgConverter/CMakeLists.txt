cmake_minimum_required(VERSION 3.11)
project(Negate CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Политика для target_link_libraries
cmake_policy(SET CMP0079 NEW)

# Создаем исполняемый файл
add_executable(imgconv main.cpp)

# Добавляем Include директории
target_include_directories(imgconv PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../ImgLib)

# Линкуем с ImgLib
target_link_libraries(imgconv PRIVATE ImgLib)

# Для MinGW особая линковка
if (CMAKE_SYSTEM_NAME MATCHES "Mingw")
    target_link_libraries(imgconv PRIVATE -lstdc++)
endif()