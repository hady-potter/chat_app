cmake_minimum_required(VERSION 3.22)
project(CLINT)
add_executable(clint src/clint.c src/talk.c)
target_include_directories(clint PUBLIC include/)