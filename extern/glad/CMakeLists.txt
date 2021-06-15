cmake_minimum_required(VERSION 3.13.4)

project(Glad)

add_library(glad include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)