cmake_minimum_required(VERSION 3.21)
project(word)

set(CMAKE_CXX_STANDARD 14)

add_executable(word main.cpp word.h word.cpp jsoncpp.cpp word_io.cpp database.h)
