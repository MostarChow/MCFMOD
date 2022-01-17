
#include "AppDelegate.h"
#include "cocos2d.h"
#include <jni.h>

#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#include "fmod_android/inc/fmod.hpp"
#include "fmod_android/inc/fmod_studio.hpp"
#include "fmod_android/inc/fmod_errors.h"

#define LOG_TAG "main"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

FMOD::Studio::System *studioSystem;

const char *GetMediaPath(const char *fileName)
{
    char *filePath = (char *)calloc(256, sizeof(char));
    strcat(filePath, "file:///android_asset/");
    strcat(filePath, fileName);
    return filePath;
}

void loadBank()
{
    void *extradriverdata = NULL;
    // 创建studio对象
    FMOD::Studio::System::create(&studioSystem);
    // 创建core对象
    FMOD::System *coreSystem = NULL;
    studioSystem->getCoreSystem(&coreSystem);
    // 初始化studio
    studioSystem->initialize(2048, FMOD_INIT_NORMAL, FMOD_INIT_NORMAL, extradriverdata);
    // 加载bank
    FMOD::Studio::Bank *masterBank = NULL;
    studioSystem->loadBankFile(GetMediaPath("Master.bank"), FMOD_STUDIO_INIT_NORMAL, &masterBank);
    FMOD::Studio::Bank* stringsBank = NULL;
    studioSystem->loadBankFile(GetMediaPath("Master.strings.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
    FMOD::Studio::Bank *sfxBank = NULL;
    studioSystem->loadBankFile(GetMediaPath("sfx.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &sfxBank);
    FMOD::Studio::Bank *musicBank = NULL;
    studioSystem->loadBankFile(GetMediaPath("music.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &musicBank);
}

void playEvent(const char *path)
{
    // 创建示例对象并加载
    FMOD::Studio::EventDescription *desc = NULL;
    studioSystem->getEvent(path, &desc);
    desc->loadSampleData();

    FMOD::Studio::EventInstance *instance = NULL;
    desc->createInstance(&instance);
    // 播放
    instance->start();
    instance->release();
    studioSystem->update();
}

void stopEvent(const char *path)
{
    FMOD::Studio::EventDescription *desc = NULL;
    studioSystem->getEvent(path, &desc);
    // 获取实例对象
    FMOD::Studio::EventInstance *instance = NULL;
    int count = 0;
    desc->getInstanceCount(&count);
    desc->getInstanceList(&instance, count, &count);
    // 停止播放
    instance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
    studioSystem->update();
}


extern "C"
{
    /*JNI_CALL_FUNCTION*/
    JNIEXPORT void Java_org_cocos2dx_javascript_AppActivity_loadBank(JNIEnv*env, jobject thiz)
    {
        loadBank();
    }
    JNIEXPORT void Java_org_cocos2dx_javascript_AppActivity_playEvent(JNIEnv*env, jobject thiz, jstring path)
    {
        std::string pathStr = cocos2d::JniHelper::jstring2string(path);
        const char *cPath = pathStr.c_str();
        playEvent(cPath);
    }
    JNIEXPORT void Java_org_cocos2dx_javascript_AppActivity_stopEvent(JNIEnv*env, jobject thiz, jstring path)
    {
        std::string pathStr = cocos2d::JniHelper::jstring2string(path);
        const char *cPath = pathStr.c_str();
        stopEvent(cPath);
    }
}

