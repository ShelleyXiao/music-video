//
// Created by ShaudXiao on 2018/3/28.
//

#include "opensl_es_context.h"

#define LOG_TAG "OpenSLESContext"

OpenSLESContext* OpenSLESContext::instance = new OpenSLESContext();

void OpenSLESContext::init() {
    LOGI("create engine");
    SLresult result = createEngine();
    LOGI("create engine result %d\n", result_to_string(result));
    if(SL_RESULT_SUCCESS == result) {
        LOGI("Realize this engine object\n");
        result = RealizeObject(engineObject);
        if(SL_RESULT_SUCCESS == result) {
            LOGI("Get the engine interface\n");
            result = GetEngineInterface();
        }
    }
}

OpenSLESContext::OpenSLESContext() {
    isInited = false;
}

OpenSLESContext* OpenSLESContext::getInstance() {
    if(!instance->isInited) {
        instance->init();
        instance->isInited = true;
    }

    return instance;
}

OpenSLESContext::~OpenSLESContext() {

}

