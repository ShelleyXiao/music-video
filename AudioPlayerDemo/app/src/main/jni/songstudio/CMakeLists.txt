cmake_minimum_required(VERSION 3.4.1)

project(songstudio)

message("progject : ${PROJECT_SOURCE_DIR}")


include_directories(${PROJECT_SOURCE_DIR}/3rparty/ffmpeg/include)
include_directories(${PROJECT_SOURCE_DIR}/libcommon)

add_subdirectory(${PROJECT_SOURCE_DIR}/libcommon)
add_subdirectory(${PROJECT_SOURCE_DIR}/libmedia)
add_subdirectory(${PROJECT_SOURCE_DIR}/libmusicdecoder)



add_definitions("-D__STDC_CONSTANT_MACROS")

#link_directories(${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a)

#set(ffmpeg_lib
#    ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libavcodec.a
#    ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libavfilter.a
#    ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libavformat.a
#    ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libavutil.a
#    ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libpostproc.a
#    ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libswresample.a
#    ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libswscale.a
#    ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libvo-aacenc.a
#    ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libx264.a
#    ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libfdk-aac.a
#)

#link_libraries(${ffmpeg_lib})


#link_libraries(${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libfdk-acc.a );

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )


find_library(OpenSLES-lib OpenSLES)
find_library(android-lib android)
find_library(z-lib z)
find_library(fdk-acc-lib fdk-acc ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a)


add_library( # Sets the name of the library.
             soundstudio

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             SoundTrackController.cpp )


target_link_libraries( # Specifies the target library.
                       soundstudio
                       ${log-lib}
                       ${OpenSLES-lib}
                       ${android-lib}
                       ${z-lib}
                        )

#target_link_libraries(soundstudio ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libfdk-acc.a)
target_link_libraries(soundstudio ${PROJECT_SOURCE_DIR}/3rparty/prebuilt/armv7-a/libx264.a)
target_link_libraries(soundstudio ${PROJECT_SOURCE_DIR}/libcommon/${ANDROID_ABI}/libcommon.a)
target_link_libraries(soundstudio ${PROJECT_SOURCE_DIR}/libmedia/${ANDROID_ABI}/libmedia.a)
target_link_libraries(soundstudio ${PROJECT_SOURCE_DIR}/libmusicdecoder/${ANDROID_ABI}/libmusicdecoder.a)
