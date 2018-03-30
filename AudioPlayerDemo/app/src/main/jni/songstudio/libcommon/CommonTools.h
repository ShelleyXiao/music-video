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

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

typedef signed short SInt16;
typedef unsigned char byte;

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

#define AUDIO_PCM_OUTPUT_CHANNEL 2

//合并两个float，返回一个short
inline SInt16 TPMixSamplesFloat(float a, float b) {
    int tmp = a < 0 && b < 0 ? ((int) a + (int) b) - (((int) a * (int) b) / INT16_MIN) : (a > 0 && b > 0 ? ((int) a + (int) b) - (((int) a * (int) b) / INT16_MAX) : a + b);
    return tmp > INT16_MAX ? INT16_MAX : (tmp < INT16_MIN ? INT16_MIN : tmp);
}

//把一个short转换为一个长度为2的byte数组
inline void converttobytearray(SInt16 source, byte* bytes2) {
    bytes2[0] = (byte) (source & 0xff);
    bytes2[1] = (byte) ((source >> 8) & 0xff);
}

//调节音量的方法
inline SInt16 adjustAudioVolume(SInt16 source, float volume) {
    /**
    SInt16 result = source;
    int temp = (int) ((int) source * volume);
    if (temp < -0x8000) {
        result = -0x8000;
    } else if (temp > 0x7FFF) {
        result = 0x7FFF;
    } else {
        result = (short) temp;
    }
    return result;
    **/

    SInt16 result = source;
    int temp = (int) ((int) source * volume);
    int sign = 1;
    if (temp < 0) {
        sign = -1;
    }
    int abstemp = abs(temp);
    if (abstemp < 29490) {
        result = temp;
    }
    else if (abstemp > 46285) {
        result = 32767 * sign;
    }
    else if (abstemp > 32630) {
        result = ((abstemp - 29490) / 8 + 30668)*sign;
    }
    else {
        result = ((abstemp - 29490) / 2 + 29490)*sign;
    }
    return result;
}


//调节采样的音量---非清唱时候最终合成伴奏与录音的时候，判断如果accompanyVolume不是1.0的话，先调节伴奏的音量；而audioVolume是在读出的字节流转换为short流的时候调节的。
inline void adjustSamplesVolume(SInt16 *samples, int size, float accompanyVolume) {
    if (accompanyVolume != 1.0) {
        for (int i = 0; i < size; i++) {
            samples[i] = adjustAudioVolume(samples[i], accompanyVolume);
        }
    }
}

//将一个short数组转换为一个byte数组---清唱时由于不需要和伴奏合成，所以直接转换;还有一个是当解码完成之后，需要将short变为byte数组，写入文件
inline void convertByteArrayFromShortArray(SInt16 *shortarray, int size, byte *bytearray) {
    byte* tmpbytearray = new byte[2];
    for (int i = 0; i < size; i++) {
        converttobytearray(shortarray[i], tmpbytearray);
        bytearray[i * 2] = tmpbytearray[0];
        bytearray[i * 2 + 1] = tmpbytearray[1];
    }
    delete[] tmpbytearray;
}




#endif //AUDIOPLAYERDEMO_COMMONTOOLS_H
