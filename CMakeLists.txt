cmake_minimum_required(VERSION 3.17)
project(trace_decode)

set(CMAKE_CXX_STANDARD 14)

# add extra include directories
include_directories(/opt/homebrew/include)

# add extra lib directories
link_directories(/opt/homebrew/lib)

# set(BUILD_ARCH "-x86_64")

add_executable(trace_decode main.cpp base64.h base64.cpp decode.h decode.cpp)
