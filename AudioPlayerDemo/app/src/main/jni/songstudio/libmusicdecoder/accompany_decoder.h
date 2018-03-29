//
// Created by ShaudXiao on 2018/3/28.
//

#ifndef AUDIOPLAYERDEMO_ACCOMPANY_DECODER_H
#define AUDIOPLAYERDEMO_ACCOMPANY_DECODER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../libcommon/CommonTools.h"
#include "../libcommon/packet_queue.h"

#ifndef UINT64_C
#define UINT64_C(value)__CONCAT(value, ULL)
#endif

#ifndef INT64_MIN
#define INT64_MIN  (-9223372036854775807LL - 1)
#endif

#ifndef INT64_MAX
#define INT64_MAX	9223372036854775807LL
#endif

extern "C" {
#include "../3rparty/ffmpeg/include/libavcodec/avcodec.h"
#include "../3rparty/ffmpeg/include/libavformat/avformat.h"
#include "../3rparty/ffmpeg/include/libavutil/avutil.h"
#include "../3rparty/ffmpeg/include/libavutil/frame.h"
#include "../3rparty/ffmpeg/include/libavutil/samplefmt.h"
#include "../3rparty/ffmpeg/include/libavutil/common.h"
#include "../3rparty/ffmpeg/include/libavutil/channel_layout.h"
#include "../3rparty/ffmpeg/include/libavutil/opt.h"
#include "../3rparty/ffmpeg/include/libavutil/imgutils.h"
#include "../3rparty/ffmpeg/include/libavutil/mathematics.h"
#include "../3rparty/ffmpeg/include/libswscale/swscale.h"
#include "../3rparty/ffmpeg/include/libswresample/swresample.h"
}

#define OUT_PUT_CHANNELS 2

class AccompanyDecoder {
    bool seek_req;
    bool seek_resp;
    float seek_seconds;

    float actualSeekPosition;

    AVFormatContext *avFormatContext;
    AVCodecContext *avCodecContext;
    int stream_index;
    double time_base;
    AVFrame *pAudioFrame;
    AVPacket packet;

    char *accompanyFilePath;

    bool seek_success_read_frame_success;
    int packetBufferSize;

    short *audioBuffer;
    float position;
    int audioBufferCursor;
    int audioBufferSize;
    float duration;
    bool isNeedFirstFrameCorrectFlag;
    float firstFrameCorrectionInSec;

    SwrContext *swrContext;
    void *swrBuffer;
    int swrBufferSize;

    int init(const char*fileString);
    int readSamples(short *samples, int size);
    int readFrame();
    bool audioCodecInSuported();

public:
    AccompanyDecoder();
    virtual ~AccompanyDecoder();

    virtual int getMusicMeta(const char* fileString, int *metaData);

    virtual void init(const char*fileString, int packetBufferSizeParam);

    virtual AudioPacket* decodePacket();

    virtual void destroy();

    void setSeekReq(bool seekReqParam) {
        seek_req = seekReqParam;
        if(seek_req) {
            seek_resp = false;
        }
    }

    bool hasSeekReq() {
        return seek_req;
    }

    bool hasSeekResp() {
        return seek_resp;
    }

    void setPosition(float seconds) {
        actualSeekPosition = -1;
        this->seek_seconds = seconds;
        this->seek_req = true;
        this->seek_resp = false;
    }

    float getPosition() {
        float ret = actualSeekPosition;
        if(ret != -1) {
            actualSeekPosition = -1;
        }

        return ret;
    }

    virtual void seek_frame();
};

#endif //AUDIOPLAYERDEMO_ACCOMPANY_DECODER_H
