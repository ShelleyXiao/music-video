//
// Created by ShaudXiao on 2018/3/29.
//

#include "accompany_decoder_controller.h"

void *AccompanyDecoderController::startDecoderThread(void *ptr) {
    LOGI("enter AccompanyDecoderController::startDecoderThread");
    AccompanyDecoderController *decoderController
            = (AccompanyDecoderController *) ptr;
    int getLockCode = pthread_mutex_lock(&decoderController->mLock);
    while (decoderController->isRunning) {
        decoderController->decoderSongPacket();
        if (decoderController->packetPool->geDecoderAccompanyPacketQueueSize() >
            QUEUE_SIZE_MAX_THRESHOLD) {
            pthread_cond_wait(&decoderController->mCondition,
                              &decoderController->mLock);
        }
    }

    pthread_mutex_unlock(&decoderController->mLock);
}

void AccompanyDecoderController::initDecoderThread() {
    isRunning = true;
    pthread_mutex_init(&mLock, NULL);
    pthread_cond_init(&mCondition, NULL);
    pthread_create(&songDecoderThread, NULL,
                   startDecoderThread, this);
}

void AccompanyDecoderController::decoderSongPacket() {
    AudioPacket *accompanyPacket = accompanyDecoder->decodePacket();
    accompanyPacket->action = AudioPacket::AUDIO_PACKET_ACTION_PLAY;
    packetPool->pushAccompanyPacketToQueue(accompanyPacket);
}

void AccompanyDecoderController::destroyDecoderThread() {
    isRunning = false;
    void *status;
    int getLockCode = pthread_mutex_lock(&mLock);
    pthread_cond_signal(&mCondition);
    pthread_mutex_unlock(&mLock);
    pthread_join(songDecoderThread, &status);
    pthread_mutex_destroy(&mLock);
    pthread_cond_destroy(&mCondition);
}


AccompanyDecoderController::AccompanyDecoderController() {
    accompanyDecoder = NULL;
    playPosition = 0.0f;
}

AccompanyDecoderController::~AccompanyDecoderController() {

}


void AccompanyDecoderController::initAccompanyDecoder(const char *accompanyPath) {
    accompanyDecoder = new AccompanyDecoder();
    accompanyDecoder->init(accompanyPath, accompanyPacketBufferSize);
}

/** 根据伴奏文件与原唱文件得到采样率以及比特率赋值给全局变量，
 * 并且将伴奏文件的采样率与比特率放入metaData返回 **/
virtual int
AccompanyDecoderController::getMusicMeta(const char *accompanyPath, const char *originalSongPath,
                                         int *accompanyMetaData) {
    AccompanyDecoder *accompanyDecoder = new AccompanyDecoder();
    accompanyDecoder->getMusicMeta(accompanyPath, accompanyMetaData);
    delete accompanyDecoder;
    accompanySampleRate = accompanyMetaData[0];

    return 0;
};

/** 初始两个decoder,并且根据上一步算出的采样率，计算出伴奏和原唱的bufferSize **/
void
AccompanyDecoderController::init(const char *accompanyPath, const char *originalSongPath,
                                 float packetBufferTimePercent) {
    volume = 0.0f;
    accompanyMax = 1.0f;

    //计算计算出伴奏和原唱的bufferSize
    int accompanyByteCountSize =
            accompanySampleRate * CHANNEL_PER_FRAME * BITS_PER_CHANNEL
            / BITS_PER_BYTE;
    accompanyPacketBufferSize = (int) ()(accompanyByteCountSize / 2) * packetBufferTimePercent);

    initAccompanyDecoder(accompanyPath);

    packetPool = PacketPool::getInstance();
    packetPool->initDecoderAccompanyPacketQueue();
    initDecoderThread();
}

/** 读取samples,返回实际读取的sample的个数
 * 并且将accompanyPacket放入到accompanyQueue中，
 * 如果有originalSongPacket销毁 **/
int AccompanyDecoderController::readSamples(short *samples,
                                            int size,
                                            int *slientSizeArr) {
    int result = -1;
    AudioPacket *accompayPacket = NULL;
    packetPool->getDecoderAccompanyPacket(&accompayPacket, true);
    if (NULL != accompayPacket) {
        int samplePacketSize = accompayPacket->size;
        if (samplePacketSize != -1 && samplePacketSize <= size) {
            memcpy(samples, accompayPacket->buffer, samplePacketSize * 2);

            adjustSamplesVolume(samples, samplePacketSize, volume / accompanyMax);
            result = samplePacketSize;

        }
    } else {
        result = -2;
    }

    if (packetPool->geDecoderAccompanyPacketQueueSize() < QUEUE_SIZE_MIN_THRESHOLD) {
        int getLockCode = pthread_mutex_lock(&this->mLock);
        if (result != -1) {
            pthread_cond_signal(&this->mCondition);
        }
        pthread_mutex_unlock(&this->mLock);
    }

    return result;
}


float AccompanyDecoderController::getPlayPosition() {
    return playPosition;
}

/** 销毁这个controller **/
void AccompanyDecoderController::destroy() {
    destroyDecoderThread();
    packetPool->abortDecoderAccompanyPacketQueue();
    packetPool->destoryAccompanyPacketQueue();
    if (NULL != accompanyDecoder) {
        accompanyDecoder->destroy();
        delete accompanyDecoder;
        accompanyDecoder = NULL;
    }
}
