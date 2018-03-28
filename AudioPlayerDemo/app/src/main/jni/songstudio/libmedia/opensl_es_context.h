//
// Created by ShaudXiao on 2018/3/28.
//

#ifndef AUDIOPLAYERDEMO_OPENSL_ES_CONTEXT_H
#define AUDIOPLAYERDEMO_OPENSL_ES_CONTEXT_H

#include "opensl_es_utils.h.h"
#include "../libcommon/CommonTools.h"

class OpenSLESContext {
private:
    SLObjectItf engineObject;
    SLEngineItf engineEngine;

    bool isInited;

    SLresult createEngine() {
        SLEngineOption engineOption[] = {
                {(SLuint32) SL_ENGINEOPTION_THREADSAFE, (SLuint32) SL_BOOLEAN_TRUE},
        };

        return slCreateEngine(&engineObject,
                              ARRAY_LEN(engineOption), engineOption,
                              0,
                              0,
                              0);
    }

    SLresult RealizeObject(SLObjectItf object) {
        return (*object)->Realize(object, SL_BOOLEAN_FALSE);
    }

    SLresult GetEngineInterface() {
        return (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
    }

    OpenSLESContext();
    void init();

    static OpenSLESContext* instance;

public:
    static OpenSLESContext* getInstance();
    virtural ~OpenSLESContext();

    SLEngineItf  getEngine() {
        return engineEngine;
    }
};

#endif //AUDIOPLAYERDEMO_OPENSL_ES_CONTEXT_H
