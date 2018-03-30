//
// Created by ShaudXiao on 2018/3/28.
//
#include "packet_pool.h"

PacketPool::PacketPool() {

}

PacketPool::~PacketPool() {

}

PacketPool *PacketPool::instance = new PacketPool();

PacketPool *PacketPool::getInstance() {
    return instance;
}

/** 解码出来的伴奏的queue的所有操作 **/
void PacketPool::initDecoderAccompanyPacketQueue() {
    const char *name = "decoder Accompany packet queue";
    decoderAccompanyPacketQueue = new PacketQueue(name);
}

void PacketPool::abortDecoderAccompanyPacketQueue() {
    if (NULL != decoderAccompanyPacketQueue) {
        decoderAccompanyPacketQueue->abort();
    }
}

void PacketPool::destoryDecoderAccompanyPacketQueue() {
    if (NULL != decoderAccompanyPacketQueue) {
        delete decoderAccompanyPacketQueue;
        decoderAccompanyPacketQueue = NULL;
    }
}

int PacketPool::getDecoderAccompanyPacket(AudioPacket **audioPacket, bool block) {
    int result = -1;
    if (NULL != decoderAccompanyPacketQueue) {
        result = decoderAccompanyPacketQueue->get(audioPacket, block);
    }

    return result;
}

void PacketPool::pushDecoderAccompanyPacketToQueue(AudioPacket *audioPacket) {
    decoderAccompanyPacketQueue->put(audioPacket);
}

void PacketPool::clearDecoderAccompanyPacketToQueue() {
    decoderAccompanyPacketQueue->flush();
}

int PacketPool::geDecoderAccompanyPacketQueueSize() {
    return decoderAccompanyPacketQueue->size();
}

/** 解码出来的原唱的queue的所有操作 **/
void PacketPool::initDecoderOriginalSongPacketQueue() {
    const char *name = "decoder orignal song packet queue";
    decoderOriginalSongPacketQueue = new PacketQueue(name);
}


void PacketPool::abortDecoderOriginalSongPacketQueue() {
    if (NULL != decoderOriginalSongPacketQueue) {
        decoderOriginalSongPacketQueue->abort();
    }
}

void PacketPool::destoryDecoderOriginalSongPacketQueue() {
    if (NULL != decoderOriginalSongPacketQueue) {
        delete decoderOriginalSongPacketQueue;
        decoderOriginalSongPacketQueue = NULL;
    }
}

int PacketPool::getDecoderOriginalSongPacket(AudioPacket **audioPacket, bool block) {
    int result = -1;
    if (NULL != decoderOriginalSongPacketQueue) {
        result = decoderOriginalSongPacketQueue->get(audioPacket, block);
    }

    return result;
}

void PacketPool::pushDecoderOriginalSongPacketToQueue(AudioPacket *audioPacket) {
    decoderOriginalSongPacketQueue->put(audioPacket);
}

void PacketPool::clearDecoderOriginalSongPacketToQueue() {
    decoderOriginalSongPacketQueue->flush();
}

int PacketPool::getDecoderOriginalSongPacketQueueSize() {
    return decoderOriginalSongPacketQueue->size();
}

/** 人声的packet queue的所有操作 **/
void PacketPool::initAudioPacketQueue() {
    const char *name = "audio packet queue";
    audioPacketQueue = new PacketQueue(name);
}

void PacketPool::abortAudioPacketQueue() {
    if (NULL != audioPacketQueue) {
        audioPacketQueue->abort();
    }
}

void PacketPool::destoryAudioPacketQueue() {
    if (NULL != audioPacketQueue) {
        delete audioPacketQueue;
        audioPacketQueue = NULL;
    }
}

int PacketPool::getAudioPacket(AudioPacket **audioPacket, bool block) {
    int result = -1;
    if (NULL != audioPacketQueue) {
        result = audioPacketQueue->get(audioPacket, block);
    }

    return result;
}

void PacketPool::pushAudioPacketToQueue(AudioPacket *audioPacket) {
    audioPacketQueue->put(audioPacket);
}

void PacketPool::clearAudioPacketToQueue() {
    audioPacketQueue->flush();
}

int PacketPool::getAudioPacketQueueSize() {
    return audioPacketQueue->size();
}

/** 伴奏的packet queue的所有操作 **/
void PacketPool::initAccompanyPacketQueue() {
    const char *name = "Live packet queue";
    accompanyPacketQueue = new PacketQueue(name);
}

void PacketPool::abortAccompanyPacketQueue() {
    if (NULL != accompanyPacketQueue) {
        accompanyPacketQueue->abort();
    }
}

void PacketPool::destoryAccompanyPacketQueue() {
    if (NULL != accompanyPacketQueue) {
        delete accompanyPacketQueue;
        accompanyPacketQueue = NULL;
    }
}

int PacketPool::getAccompanyPacket(AudioPacket **accompanyPacket, bool block) {
    int result = -1;
    if (NULL != accompanyPacketQueue) {
        result = accompanyPacketQueue->get(accompanyPacket, block);
    }

    return result;
}

void PacketPool::pushAccompanyPacketToQueue(AudioPacket *accompanyPacket) {
    accompanyPacketQueue->put(accompanyPacket);
}

int PacketPool::getAccompanyPacketQueueSize() {
    return accompanyPacketQueue->size();
}

void PacketPool::clearAccompanyPacketQueue() {
    accompanyPacketQueue->flush();
}

/** 直播发送的packet queue的所有操作 **/
void PacketPool::initLivePacketQueue() {
    const char *name = "Live packet queue";
    livePacketQueue = new PacketQueue(name);
}

void PacketPool::abortLivePacketQueue() {
    if (NULL != audioPacketQueue) {
        audioPacketQueue->abort();
    }
}

void PacketPool::destoryLivePacketQueue() {
    if (NULL != audioPacketQueue) {
        delete audioPacketQueue;
        audioPacketQueue = NULL;
    }
}

int PacketPool::getLivePacket(AudioPacket **livePacket, bool block) {
    int result = -1;
    if (NULL != audioPacketQueue) {
        result = audioPacketQueue->get(livePacket, block);
    }

    return result;
}

void PacketPool::pushLivePacketToQueue(AudioPacket *livePacket) {
    audioPacketQueue->put(livePacket);
}

int PacketPool::getLivePacketQueueSize() {
    return audioPacketQueue->size();
}

/** 直播接收的packet queue的所有操作 **/
void PacketPool::initLiveSubscriberPacketQueue() {
    const char *name = "live subcriber packet queue";
    liveSubscriberPacketQueue = new PacketQueue(name);
}

void PacketPool::abortLiveSubscriberPacketQueue() {
    if (NULL != liveSubscriberPacketQueue) {
        liveSubscriberPacketQueue->abort();
    }
}

void PacketPool::destoryLiveSubscriberPacketQueue() {
    if (NULL != liveSubscriberPacketQueue) {
        delete liveSubscriberPacketQueue;
        liveSubscriberPacketQueue = NULL;
    }
}

int PacketPool::getLiveSubscriberPacket(AudioPacket **livePacket, bool block) {
    int result = -1;
    if (NULL != liveSubscriberPacketQueue) {
        result = liveSubscriberPacketQueue->get(livePacket, block);
    }

    return result;
}

void PacketPool::pushLiveSubscriberPacketToQueue(AudioPacket *livePacket) {
    liveSubscriberPacketQueue->put(livePacket);
}

int PacketPool::getLiveSubscriberPacketQueueSize() {
    return liveSubscriberPacketQueue->size();
}

/** 试音的packet queue的所有操作 **/
void PacketPool::initTuningPacketQueue() {
    const char *name = "tuning packet queue";
    tuningPacketQueue = new PacketQueue(name);
}

void PacketPool::abortTuningPacketQueue() {
    if (NULL != tuningPacketQueue) {
        tuningPacketQueue->abort();
    }
}

void PacketPool::destoryTuningPacketQueue() {
    if (NULL != tuningPacketQueue) {
        delete tuningPacketQueue;
        tuningPacketQueue = NULL;
    }
}

int PacketPool::getTuningPacket(AudioPacket **livePacket, bool block) {
    int result = -1;
    if (NULL != tuningPacketQueue) {
        result = tuningPacketQueue->get(livePacket, block);
    }

    return result;
}

void PacketPool::pushTuningPacketToQueue(AudioPacket *livePacket) {
    tuningPacketQueue->put(livePacket);
}

int PacketPool::getTuningPacketQueueSize() {
    return tuningPacketQueue->size();
}
