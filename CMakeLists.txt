cmake_minimum_required(VERSION 3.17)
project(trace_decode)

set(CMAKE_CXX_STANDARD 14)

set(DECODER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(SNAPPY_PATH "${DECODER_DIR}/submodules/snappy-1.1.9")

link_libraries(snappy)

include_directories(${SNAPPY_PATH})
FIND_LIBRARY(SNAPPY_LIB NAMES libsnappy.a HINTS ${SNAPPY_PATH} NO_DEFAULT_PATH)

add_executable(trace_decode main.cpp base64.h base64.cpp decode.h decode.cpp)

target_link_libraries(trace_decode -Lsnappy ${SNAPPY_LIB})
