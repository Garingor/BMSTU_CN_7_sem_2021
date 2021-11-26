cmake_minimum_required(VERSION 3.20)
project(lab2_net C)

set(CMAKE_C_STANDARD 99)

add_executable(lab2_net main.c client.c server.c)
