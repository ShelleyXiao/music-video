//
// Created by ShaudXiao on 2018/3/28.
//

#ifndef AUDIOPLAYERDEMO_OPENSL_ES_UTILS_H_H
#define AUDIOPLAYERDEMO_OPENSL_ES_UTILS_H_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

static const char* result_to_string(SLresult result) {
    const char* str = 0;
    switch(result) {
        case SL_RESULT_SUCCESS:
            str = "Success";
            break;

        case SL_RESULT_PRECONDITIONS_VIOLATED:
            str = "Preconditions violated";
            break;

        case SL_RESULT_PARAMETER_INVALID:
            str = "Parameter invalid";
            break;

        case SL_RESULT_MEMORY_FAILURE:
            str = "Memory failure";
            break;

        case SL_RESULT_RESOURCE_ERROR:
            str = "Resource error";
            break;

        case SL_RESULT_RESOURCE_LOST:
            str = "Resource lost";
            break;

        case SL_RESULT_IO_ERROR:
            str = "IO error";
            break;

        case SL_RESULT_BUFFER_INSUFFICIENT:
            str = "Buffer insufficient";
            break;

        case SL_RESULT_CONTENT_CORRUPTED:
            str = "Success";
            break;

        case SL_RESULT_CONTENT_UNSUPPORTED:
            str = "Content unsupported";
            break;

        case SL_RESULT_CONTENT_NOT_FOUND:
            str = "Content not found";
            break;

        case SL_RESULT_PERMISSION_DENIED:
            str = "Permission denied";
            break;

        case SL_RESULT_FEATURE_UNSUPPORTED:
            str = "Feature unsupported";
            break;

        case SL_RESULT_INTERNAL_ERROR:
            str = "Internal error";
            break;

        case SL_RESULT_UNKNOWN_ERROR:
            str = "Unknown error";
            break;

        case SL_RESULT_OPERATION_ABORTED:
            str = "Operation aborted";
            break;

        case SL_RESULT_CONTROL_LOST:
            str = "Control lost";
            break;

        default:
            str = "Unknown code";
    }

    return str;
}


static int get_channel_mask(int channels ) {
    int channelMask = SL_SPEAKER_FRONT_CENTER;
    switch (channels) {
        case 1:
            channelMask = SL_SPEAKER_FRONT_CENTER;
        case 2:
            channelMask = SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
    }

    return channelMask;
}

static int opensl_get_sample_rate(int sampleRate) {
    int samplesPerSec = SL_SAMPLINGRATE_44_1;
    switch (sampleRate) {
        case 8000:
            samplesPerSec = SL_SAMPLINGRATE_8;
            break;
        case 11025:
            samplesPerSec = SL_SAMPLINGRATE_11_025;
            break;
        case 12000:
            samplesPerSec = SL_SAMPLINGRATE_12;
            break;
        case 16000:
            samplesPerSec = SL_SAMPLINGRATE_16;
            break;
        case 22050:
            samplesPerSec = SL_SAMPLINGRATE_22_05;
            break;
        case 24000:
            samplesPerSec = SL_SAMPLINGRATE_24;
            break;
        case 32000:
            samplesPerSec = SL_SAMPLINGRATE_32;
            break;
        case 44100:
            samplesPerSec = SL_SAMPLINGRATE_44_1;
            break;
        case 48000:
            samplesPerSec = SL_SAMPLINGRATE_48;
            break;
        case 64000:
            samplesPerSec = SL_SAMPLINGRATE_64;
            break;
        case 88200:
            samplesPerSec = SL_SAMPLINGRATE_88_2;
            break;
        case 96000:
            samplesPerSec = SL_SAMPLINGRATE_96;
            break;
        case 192000:
            samplesPerSec = SL_SAMPLINGRATE_192;
            break;
        default:
            samplesPerSec = SL_SAMPLINGRATE_44_1;
    }

    return samplesPerSec;
}

#endif //AUDIOPLAYERDEMO_OPENSL_ES_UTILS_H_H
