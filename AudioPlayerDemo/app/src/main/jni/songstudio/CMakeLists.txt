cmake_minimum_required(VERSION 3.4.1)


set(LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__STDC_CONSTANT_MACROS")
set(CMAKE_CPP_FLAGS "${CMAKE_CPP_FLAGS} -D__STDC_CONSTANT_MACROS")

message("progject : ${CMAKE_SOURCE_DIR}")
message("SRC : ${LIB_SRC_DIR}")

include_directories(${CMAKE_SOURCE_DIR}/3rparty/ffmpeg)
include_directories(${CMAKE_SOURCE_DIR}/3rparty/ffmpeg/include)
include_directories(${CMAKE_SOURCE_DIR}/libcommon)

add_library(fdk-acc STATIC IMPORTED)
set_target_properties(fdk-acc
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/3rparty/${ANDROID_ABI}/libfdk-aac.a)

message("test: ${CMAKE_SOURCE_DIR}/3rparty/${ANDROID_ABI}/libavfilter.a")

add_library(avcodec STATIC IMPORTED)
set_target_properties(avcodec
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/3rparty/${ANDROID_ABI}/libavcodec.a)

add_library(avfilter STATIC IMPORTED)
set_target_properties(avfilter
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/3rparty/${ANDROID_ABI}/libavfilter.a)

add_library(avformat STATIC IMPORTED)
set_target_properties(avformat
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/3rparty/${ANDROID_ABI}/libavformat.a)

add_library(avutil STATIC IMPORTED)
set_target_properties(avutil
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/3rparty/${ANDROID_ABI}/libavutil.a)

add_library(postproc STATIC IMPORTED)
set_target_properties(postproc
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/3rparty/${ANDROID_ABI}/libpostproc.a)

add_library(swresample STATIC IMPORTED)
set_target_properties(swresample
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/3rparty/${ANDROID_ABI}/libswresample.a)

add_library(swscale STATIC IMPORTED)
set_target_properties(swscale
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/3rparty/${ANDROID_ABI}/libswscale.a)

add_library(vo-aacenc STATIC IMPORTED)
set_target_properties(vo-aacenc
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/3rparty/${ANDROID_ABI}/libvo-aacenc.a)

add_library(x264 STATIC IMPORTED)
set_target_properties(x264
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/3rparty/${ANDROID_ABI}/libx264.a)


message("LIB_SRC_DIR:", ${LIB_SRC_DIR})

add_subdirectory(${LIB_SRC_DIR}/libmedia)
add_subdirectory(${LIB_SRC_DIR}/libcommon)
add_subdirectory(${LIB_SRC_DIR}/libmusicdecoder)
add_subdirectory(${LIB_SRC_DIR}/3rparty)


add_library( # Sets the name of the library.
             soundstudio

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${LIB_SRC_DIR}/SoundTrackController.cpp )


target_link_libraries( # Specifies the target library.
                       soundstudio
                       libcommon
                       libmedia
                       libmusicdecoder avfilter
                      avformat
                      avcodec
                      fdk-aac
                      vo-aacenc
                      avutil
                      swscale
                      swresample
                      postproc
                      #sox
                      x264
                      GLESv2
                      OpenSLES
                      #EGL
                      z
                      #gomp
                      android
                      log
                        )

