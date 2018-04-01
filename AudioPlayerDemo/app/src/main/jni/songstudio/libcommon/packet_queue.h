//
// Created by ShaudXiao on 2018/3/28.
//

#ifndef AUDIOPLAYERDEMO_PACKET_QUEUE_H
#define AUDIOPLAYERDEMO_PACKET_QUEUE_H

#include <pthread.h>
#include "../libcommon/CommonTools.h"
#include <stdlib.h>
#include <string.h>

#define LOG_TAG "PacketQueue"

typedef struct AudioPacket {

    static const int AUDIO_PACKET_ACTION_PLAY = 0;
    static const int AUDIO_PACKET_ACTION_PAUSE = 100;
    static const int AUDIO_PACKET_ACTION_SEEK = 101;

    short *buffer;
    int size;
    float position;
    int action;

    float extra_param1;
    float extra_param2;

    AudioPacket() {
        buffer = NULL;
        size = 0;
        position = -1;
        action = 0;
        extra_param1 = 0;
        extra_param2 = 0;
    }

    ~AudioPacket() {
        if(NULL != buffer) {
            delete[] buffer;
            buffer = NULL;
        }
    }

}AudioPacket;


typedef struct AudioPacketList {
    AudioPacket *pkt;
    struct AudioPacketList* next;

    AudioPacketList() {
        pkt = NULL;
        next = NULL;
    }
} AudioPacketList;


inline void buildPaketFromBuffer(AudioPacket *audioPacket, short *samples, int sampleSize) {
    short* packetBuffer = new short[sampleSize];
    if(NULL != packetBuffer) {
        memcpy(packetBuffer, samples, sampleSize * 2);
        audioPacket->buffer = packetBuffer;
        audioPacket->size = sampleSize;
    } else {
        audioPacket->size = -1;
    }
}

class PacketQueue {

public:
    PacketQueue();
    PacketQueue(const char* queueNameParam);
    ~PacketQueue();

    void init();
    void flush();
    int put(AudioPacket* audioPacket);

    int get(AudioPacket **pAudioPacket, bool block);

    int size();

    void abort();

private:
    AudioPacketList *mFirst;
    AudioPacketList *mLast;

    int mNbPackets;
    bool mAbortRequest;
    pthread_mutex_t mLock;
    pthread_cond_t mCondition;
    const char* queueName;
};

#endif //AUDIOPLAYERDEMO_PACKET_QUEUE_H
