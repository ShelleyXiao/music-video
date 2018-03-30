//
// Created by ShaudXiao on 2018/3/28.
//

#include <SLES/OpenSLES.h>
#include "sound_service.h"


SLresult SoundService::RegisterPlayerCallback() {
    return (*slientAudioPlayerBufferQueue)->RegisterCallback(audioPlayerBufferQueue,
                                                             PlayerCallback, this);
}

SLresult SoundService::RegisterSlientPlayerCallback() {
    return (*slientAudioPlayerBufferQueue)->RegisterCallback(slientAudioPlayerBufferQueue, PlayerCallback, this); // player context
}

SoundService *SoundService::instance = new SoundService();

SoundService *SoundService::GetInstance() {
    return instance;
}

SoundService::SoundService() {
    LOGI("SoundService::SoundService()");
    playingState = PLAYING_STATE_STOPPED;
}

SoundService::~SoundService() {
    LOGI("SoundService::~SoundService()");
}

void SoundService::setOnCompletionCallback(JavaVM *g_jvm, jobject obj) {
    this->g_jvm = g_jvm;
    this->obj = obj;
}

void
SoundService::initSongDecoder(const char *accompanyPath, const char *originalPath, float percent) {

}

void SoundService::initSongDecoder(const char *accompanyPath, float percent) {
    decoderController = new AccompanyDecoderController();
    int *metaData =new int[2];
    decoderController->getMusicMeta(accompanyPath, metaData);
    this->bufferNums = 2;
    this->currentFrame = 0;
    packetBufferSize = 2 * accompanySampleRate * 2 * percent;
    bufferSize = packetBufferSize * bufferNums;

    lastCurrentTimeMills = 0;
    seekBaseMillsTime = 0;
    seekStartRecordSeconds = 0;
    seekActualSeconds = 0;
}

SLresult SoundService::initSoundTrack() {
    SLresult  result;
    OpenSLESContext *openSLESContext = OpenSLESContext::getInstance();
    engineEngine = openSLESContext->getEngine();

    result = CreateOutputMix();
    if(SL_RESULT_SUCCESS != result) {
        return result;
    }

    result = RealizeObject(outputMixObject);
    if(SL_RESULT_SUCCESS != result) {
        return result;
    }

    InitPlayerBuffer();
    result = CreateBufferQueueAudioPlayer();
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }
    result = CreateBufferQueueSlientAudioPlayer();
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }

    LOGI("Realize audio player object");
    // Realize audio player object
    result = RealizeObject(audioPlayerObject);
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }
    result = RealizeObject(slientAudioPlayerObject);
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }

    LOGI("Get audio player buffer queue interface");
    // Get audio player buffer queue interface
    result = GetAudioPlayerBufferQueueInterface();
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }
    result = GetSlientAudioPlayerBufferQueueInterface();
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }

    LOGI("Registers the player callback");
    // Registers the player callback
    result = RegisterPlayerCallback();
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }
    result = RegisterSlientPlayerCallback();
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }

    LOGI("Get audio player play interface");
    // Get audio player play interface
    result = GetAudioPlayerPlayInterface();
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }
    result = GetSlientAudioPlayerPlayInterface();
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }
    LOGI("leave init");
    return SL_RESULT_SUCCESS;

}

SLresult SoundService::play() {
    SLresult  result = SetAudioPlayerStatePlaying();
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }
    LOGI("Set the slient audio player state playing");
    result = SetSlientAudioPlayerStatePlaying();
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }
    LOGI(" Enqueue the first buffer to start");

    playingState = PLAYING_STATE_PLAYING;

    // Enqueue buffer to start
    for (int i = 0; i < bufferNums; i++) {
        int result = -1;
        if (NULL != decoderController) {
            result = decoderController->readSamples(target, packetBufferSize / 2, NULL);
        }
        // If data is read
        if (0 < result) {
            convertByteArrayFromShortArray(target, result, buffer + i * packetBufferSize);
            (*audioPlayerBufferQueue)->Enqueue(audioPlayerBufferQueue, buffer + i * packetBufferSize, result * 2);
        }
    }

    LOGI("out SoundService::play()...");
}

SLresult SoundService::stop() {
    LOGI("enter SoundService::stop()");

    playingState = PLAYING_STATE_STOPPED;
    LOGI("Set the audio player state paused");
    // Set the audio player state playing
    SLresult result = SetAudioPlayerStateStoped();
    if (SL_RESULT_SUCCESS != result) {
        LOGI("Set the audio player state paused return false");
        return result;
    }
    LOGI("Set the slient audio player state paused");
    result = SetSlientAudioPlayerStateStoped();
    if (SL_RESULT_SUCCESS != result) {
        LOGI("Set the slient audio player state paused return false");
        return result;
    }
    DestroyContext();

    LOGI("out SoundService::stop()");
}

void SoundService::producePacket() {
    LOGI("SoundService::producePacket() audio player call back method... ");
    byte* audioBuffer = buffer + (currentFrame % bufferNums) * packetBufferSize;
    int result = -1;
    if(NULL != decoderController) {
        result = decoderController->readSamples(target, packetBufferSize / 2, NULL);
        LOGI("enter SoundService::producePacket() PLAYING_STATE_PLAYING packetBufferSize=%d, result=%d",
             packetBufferSize, result);
    }
    if(result < 0) {
        convertByteArrayFromShortArray(target, result, audioBuffer);

    } else {
        JNIEnv *env;
        if(g_jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
            LOGE("%s: AttachCurrentThread() failed", __FUNCTION__);
        }
        jclass jcls = env->GetObjectClass(obj);
        jmethodID onCompletionCallback = env->GetMethodID(jcls, "onCompletion", "()V");
        LOGI("before env->CallVoidMethod");
        env->CallVoidMethod(obj, onCompletionCallback);
        LOGI("after env->CallVoidMethod");
        if(g_jvm->DetachCurrentThread() != JNI_OK) {
            LOGE("%s: DetachCurrentThread() failed", __FUNCTION__);
        }
    }
    currentFrame = (currentFrame + 1) % bufferNums;
}

int SoundService::getCurrentTimeMills() {
    SLmillisecond position = 0;
//	LOGI("enter SoundService::getCurrentTimeMills");
    if (playingState == PLAYING_STATE_PLAYING) {
        if (0 != audioPlayerObject && NULL != (*audioPlayerPlay)) {
            SLresult result = (*audioPlayerPlay)->GetPosition(audioPlayerPlay, &position);
        }
        position += seekBaseMillsTime;
        //LOGI("enter SoundService::getCurrentTimeMills playing position=%d", (int)position);
    } else {
        position = lastCurrentTimeMills;
        //LOGI("enter SoundService::getCurrentTimeMills stoped position=%d", (int)position);
    }
    lastCurrentTimeMills = position;
    return (int)position;
}

bool SoundService::isPlaying() {
    return playingState != PLAYING_STATE_STOPPED;
}
void SoundService::setVolume(float volume) {
    if (NULL != decoderController) {
        decoderController->setVolume(volume, 1.0f);
    }
}

void SoundService::DestroyContext() {
//	pthread_mutex_lock(&mLock);
    LOGI("enter SoundService::DestroyContext");
    // Destroy audio player object
    DestroyObject(audioPlayerObject);
    DestroyObject(slientAudioPlayerObject);
    LOGI("after destroy audioPlayerObject");
    // Free the player buffer
    FreePlayerBuffer();
    LOGI("after FreePlayerBuffer");
    // Destroy output mix object
    DestroyObject(outputMixObject);
    LOGI("after destroy outputMixObject");
    //destroy mad decoder
    if (NULL != decoderController) {
        decoderController->destroy();
        delete decoderController;
        decoderController = NULL;
    }
//	isRunning = false;
//	pthread_mutex_unlock(&mLock);
    LOGI("leave SoundService::DestroyContext");
}