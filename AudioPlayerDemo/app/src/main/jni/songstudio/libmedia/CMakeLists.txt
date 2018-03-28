cmake_minimum_required(VERSION 3.4.1)

set(LIBFFMEPG_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/3rparty/ffmpeg/include")
include_directories(${LIBFFMEPG_INCLUDE_DIR})

set(SRC_LIST
    	sound_service.cpp
    	opensl_es_context.cpp
)

add_library(media
            STATIC
            ${SRC_LIST}
            )

find_library(OPENSL_ES_LIBRARY OpenSLES)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libmusicdecoder);

add_library(musicdecoder STATIC IMPORTED)
set_property(TARGET musicdecoder PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/../../../libs/${ANDROID_ABI}/libflower.so")


ADD_DEFINITIONS(
        -DHAVE_CONFIG_H
        -DFPM_ARM
        -ffast-math
        -O3
)

target_link_libraries( # Specifies the target library.
                    media
                    musicdecoder
                    ${OPENSL_ES_LIBRARY})