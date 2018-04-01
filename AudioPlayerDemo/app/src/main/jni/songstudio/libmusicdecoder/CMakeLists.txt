cmake_minimum_required(VERSION 3.4.1)

set(LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/ffmpeg/include)
include_directories(${CMAKE_SOURCE_DIR}/libcommon)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DHAVE_CONFIG_H -DFPM_ARM -ffast-math -O3")
set(CMAKE_CPP_FLAGS "${CMAKE_CPP_FLAGS} -DHAVE_CONFIG_H -DFPM_ARM -ffast-math -O3")


set(SRC_LIST
            ${LIB_SRC_DIR}/accompany_decoder_controller.cpp
            ${LIB_SRC_DIR}/accompany_decoder.cpp
)


add_library(libmusicdecoder STATIC ${SRC_LIST})
target_link_libraries(libmusicdecoder libcommontool)