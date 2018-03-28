//
// Created by ShaudXiao on 2018/3/28.
//

#include "packet_queue.h"

PacketQueue::PacketQueue() {
    init();
}

PacketQueue::PacketQueue(const char *queueNameParam) {
    init();
    queueName = queueNameParam;
}


void PacketQueue::init() {
    int initLockCode = pthread_mutex_init(&mLock, NULL);
    int initConditionCode = pthread_cond_init(&mCondition, NULL);

    mNbPackets = 0;
    mFirst = NULL;
    mLast = NULL;
    mAbortRequest = false;
}

PacketQueue::~PacketQueue() {
    flush();
    pthread_mutex_destroy(&mLock);
    pthread_cond_destroy(&mCondition);
}

void PacketQueue::flush() {
    LOGI("%s flush .... and this time the queue size is %d", queueName, size());
    AudioPacketList *pkt, *pkt1;

    AudioPacket *audioPacket;
    pthread_mutex_lock(&mLock);

    for(pkt = mFirst; pkt != NULL; pkt= pkt1) {
        pkt1 = pkt->next;
        audioPacket = pkt->pkt;
        if(NULL != audioPacket) {
            delete audioPacket;
        }
        delete  pkt;
        pkt = NULL;
    }

    mLast = NULL;
    mFirst = NULL;
    mNbPackets = 0;

    pthread_mutex_unlock(&mLock);
}

int PacketQueue::put(AudioPacket* audioPacket) {
    if(!audioPacket) {
        return -1;
    }
    if(mAbortRequest) {
        delete audioPacket;
        audioPacket = NULL;
    }
    AudioPacketList *pkt1 = new AudioPacketList();
    if(!pkt1) {
        return -1;
    }

    pkt1->pkt = audioPacket;
    pkt1->next = NULL;

    int get_lock_code = pthread_mutex_lock(&mLock);
    if(mLast == NULL) {
        mFirst = pkt1;
    } else {
        mLast->next = pkt1;
    }

    mLast = pkt1;
    mNbPackets++;

    pthread_cond_signal(&mCondition);
    pthread_mutex_unlock(&mLock);

    return 0;

}

int PacketQueue::get(AudioPacket **pAudioPacket, bool block) {
    AudioPacketList *pkt1;
    int ret;

    pthread_mutex_lock(&mLock);
    for(;;) {
        if(mAbortRequest) {
            ret = -1;
            break;
        }
        pkt1 = mFirst;
        if(pkt1) {
            mFirst = pkt1->next;
            if(!mFirst) {
                mLast = NULL;
            }
            mNbPackets--;
            *pAudioPacket = pkt1->pkt;
            delete pkt1;
            pkt1 = NULL;
            ret = 1;
            break;
        } else if(!block) {
            ret = 0;
            break;
        } else {
            pthread_cond_wait(&mCondition, &mLock);
        }
    }
    pthread_mutex_unlock(&mLock);

    return ret;
}

int PacketQueue::size() {
    pthread_mutex_lock(&mLock);
    int size = mNbPackets;
    pthread_mutex_unlock(&mLock);
    return size;
}

void PacketQueue::abort() {
    pthread_mutex_lock(&mLock);
    mAbortRequest = true;
    pthread_cond_signal(&mCondition);
    pthread_mutex_unlock(&mLock);
}