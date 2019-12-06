# Define CMake's minimum version (must-do) and the project's name and supported languages
cmake_minimum_required(VERSION 3.8.2)
project(nega_ard)

get_board_id(my_board uno)

add_arduino_executable(nega_ard ${my_board} main.cpp)

add_arduino_library(led_lib ${my_board} neopixel/Adafruit_NeoPixel.cpp)
target_include_directories(led_lib PUBLIC neopixel)
link_arduino_library(nega_ard led_lib ${my_board})

upload_arduino_target(nega_ard "${my_board}" /dev/cu.usbmodem211)
