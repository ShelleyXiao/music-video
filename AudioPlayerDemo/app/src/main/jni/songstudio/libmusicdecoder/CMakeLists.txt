cmake_minimum_required(VERSION 3.4.1)

project(musicdecoder)

include_directories(${PROJECT_SOURCE_DIR}/../3rparty/ffmpeg/include)
include_directories(${PROJECT_SOURCE_DIR}/../libcommon)

set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/${ANDROID_ABI})

set(SRC_LIST
            ${PROJECT_SOURCE_DIR}/accompany_decoder_controller.cpp
            ${PROJECT_SOURCE_DIR}/accompany_decoder.cpp
)

link_directories(${PROJECT_SOURCE_DIR}/../libcommon)
link_libraries(libcommon.a)

link_directories(${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a)

set(ffmpeg_lib
    ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libavcodec.a
    ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libavfilter.a
    ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libavformat.a
    ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libavutil.a
    ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libpostproc.a
    ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libswresample.a
    ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libswscale.a
    ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libvo-aacenc.a
    ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libx264.a
    ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libfdk-aac.a
)

#link_libraries(${ffmpeg_lib})

ADD_DEFINITIONS(
        -DHAVE_CONFIG_H
        -DFPM_ARM
        -ffast-math
        -O3
)

add_library(musicdecoder ${SRC_LIST})

#target_link_libraries(musicdecoder ${PROJECT_SOURCE_DIR}/../libcommon/${ANDROID_ABI}/libcommon.a)
target_link_libraries(musicdecoder ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libavcodec.a)
target_link_libraries(musicdecoder ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libavfilter.a)
target_link_libraries(musicdecoder ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libavformat.a)
target_link_libraries(musicdecoder ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libavutil.a)
target_link_libraries(musicdecoder ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libpostproc.a)
target_link_libraries(musicdecoder ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libswresample.a)
target_link_libraries(musicdecoder ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libswscale.a)
target_link_libraries(musicdecoder ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libvo-aacenc.a)
target_link_libraries(musicdecoder ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libx264.a)
target_link_libraries(musicdecoder ${PROJECT_SOURCE_DIR}/../3rparty/prebuilt/armv7-a/libfdk-aac.a)