cmake_minimum_required(VERSION 3.4.1)

set(lib_src_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message("test1: ${CMAKE_SOURCE_DIR}")

include_directories(
            ${CMAKE_SOURCE_DIR}/libcommon
            ${CMAKE_SOURCE_DIR}/3rdparty/ffmpeg/include
            )


set(SRC_LIST
    	 ${lib_src_DIR}/sound_service.cpp
    	 ${lib_src_DIR}/opensl_es_context.cpp
)

add_library(libmedia
            STATIC
            ${SRC_LIST}
            )

message("media: ${PROJECT_SOURCE_DIR}")

find_library(OPENSL_ES_LIBRARY OpenSLES)


target_link_libraries( # Specifies the target library.
                    libmedia
                    libmusicdecoder
                    ${OPENSL_ES_LIBRARY})