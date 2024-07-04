cmake_minimum_required(VERSION 3.22)
project(SERVER)
add_executable(server src/server.c src/clint_handler.c)
target_include_directories(server PUBLIC include/)