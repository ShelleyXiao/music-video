cmake_minimum_required(VERSION 3.4.1)

project(common)

set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/${ANDROID_ABI})

add_library(libcommon
            ${PROJECT_SOURCE_DIR}/packet_queue.cpp
            ${PROJECT_SOURCE_DIR}/packet_pool.cpp
)