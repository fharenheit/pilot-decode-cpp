# Minimal CMake Version
cmake_minimum_required(VERSION 3.17)

# Project Information
project(TraceDecoder
        VERSION 0.1
        DESCRIPTION "Trace Data Decoding Library"
        LANGUAGES CXX)

# Minimal Compiler Version
set(CMAKE_CXX_STANDARD 14)

# Set Paths
set(DECODER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message("Current Directory : ${DECODER_DIR}")

#################
## Third Party
#################

# Find Snappy
set(SNAPPY_PATH "${DECODER_DIR}/submodules/snappy-1.1.9")
message("Snappy Directory : ${SNAPPY_PATH}")

link_libraries(snappy)
include_directories(${SNAPPY_PATH})
find_library(SNAPPY_LIB NAMES libsnappy.a HINTS ${SNAPPY_PATH} NO_DEFAULT_PATH)

# Find JDK
set(JDK_PATH "/usr/lib/jvm/java-1.8.0-openjdk-1.8.0.332.b09-1.el7_9.x86_64/include/linux")
message("JDK Include Directory : ${JDK_PATH}")


# Create Shared Library
add_library(decode SHARED base64.h base64.cpp decode.h decode.cpp stopwatch.hpp)

# Create Executable for Test
add_executable(TraceDecoder main.cpp base64.h base64.cpp decode.h decode.cpp stopwatch.hpp)

# Target Link for Executable
target_link_libraries(TraceDecoder -Lsnappy ${SNAPPY_LIB})
