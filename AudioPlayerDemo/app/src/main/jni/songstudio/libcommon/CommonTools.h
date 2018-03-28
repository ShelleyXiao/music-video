//
// Created by ShaudXiao on 2018/3/28.
//

#ifndef AUDIOPLAYERDEMO_COMMONTOOLS_H
#define AUDIOPLAYERDEMO_COMMONTOOLS_H

#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b)  (((a) > (b)) ? (b) : (a))

#define UIN64_C uint64_t
#define INT16_MAX   32767
#define INT16_MIN   -32768

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

typedef signed short SInt16;
typedef unsigned char byte;

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

#define AUDIO_PCM_OUTPUT_CHANNEL 2



#endif //AUDIOPLAYERDEMO_COMMONTOOLS_H
