//
// Created by ShaudXiao on 2018/3/29.
//

#include "libmedia/sound_service.h"
#include "com_zx_audioplayerdemo_opensles_SoundTrackController.h"
#define LOG_TAG "Sound_track_controller"


static const char *JAVA_LANG_IOEXCEPTION = "java/lang/IOException";
static const char *JAVA_LANG_OUTOFMEMORYERROR = "java/lang/OutOfMemoryError";


static void ThrowExecption(JNIEnv *env, const char *className, const char *message) {
    jclass clasz = env->FindClass(className);
    if (0 != clasz) {
        env->ThrowNew(clasz, message);
        env->DeleteLocalRef(clasz);
    }
}

static bool checkError(JNIEnv *env, SLresult result) {
    bool isError = false;
    if (SL_RESULT_SUCCESS != result) {
        const char *msg = result_to_string(result);
        ThrowExecption(env, JAVA_LANG_IOEXCEPTION, msg);

        isError = true;
    }

    return isError;
}

/*
 * Class:     com_zx_audioplayerdemo_opensles_SoundTrackController
 * Method:    setAudioDataSource
 * Signature: (Ljava/lang/String;F)Z
 */
JNIEXPORT jboolean JNICALL Java_com_zx_audioplayerdemo_opensles_SoundTrackController_setAudioDataSource
        (JNIEnv *, jobject, jstring, jfloat){

}

/*
 * Class:     com_zx_audioplayerdemo_opensles_SoundTrackController
 * Method:    getAccompanySampleRate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_zx_audioplayerdemo_opensles_SoundTrackController_getAccompanySampleRate
        (JNIEnv *, jobject){

}

/*
 * Class:     com_zx_audioplayerdemo_opensles_SoundTrackController
 * Method:    play
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_zx_audioplayerdemo_opensles_SoundTrackController_play
        (JNIEnv *, jobject){

}

/*
 * Class:     com_zx_audioplayerdemo_opensles_SoundTrackController
 * Method:    getCurrentTimeMills
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_zx_audioplayerdemo_opensles_SoundTrackController_getCurrentTimeMills
        (JNIEnv *, jobject){

}

/*
 * Class:     com_zx_audioplayerdemo_opensles_SoundTrackController
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_zx_audioplayerdemo_opensles_SoundTrackController_stop
        (JNIEnv *, jobject) {

}