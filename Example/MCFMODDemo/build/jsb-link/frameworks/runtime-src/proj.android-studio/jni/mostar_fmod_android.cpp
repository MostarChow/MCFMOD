
#include "AppDelegate.h"
#include "cocos2d.h"
#include <jni.h>

#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#include <map>

#include "fmod_android/inc/fmod.hpp"
#include "fmod_android/inc/fmod_studio.hpp"
#include "fmod_android/inc/fmod_errors.h"

#define LOG_TAG "main"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

FMOD::Studio::System *studioSystem;
std::map<float, FMOD::Studio::EventInstance *> playMap;

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
    studioSystem->initialize(1024, FMOD_INIT_NORMAL, FMOD_INIT_NORMAL, extradriverdata);
    // 加载bank
    FMOD::Studio::Bank *masterBank = NULL;
    studioSystem->loadBankFile(GetMediaPath("Master.bank"), FMOD_STUDIO_INIT_NORMAL, &masterBank);
    FMOD::Studio::Bank* stringsBank = NULL;
    studioSystem->loadBankFile(GetMediaPath("Master.strings.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
    FMOD::Studio::Bank *musicBank = NULL;
    studioSystem->loadBankFile(GetMediaPath("Music.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &musicBank);
}

void playMusicEvent(const char *path, const char *paramer, float value)
{
    // 通过event创建实例
    FMOD::Studio::EventDescription *desc = NULL;
    studioSystem->getEvent(path, &desc);
    FMOD::Studio::EventInstance *instance = NULL;
    desc->createInstance(&instance);

    // 设置参数和id
    FMOD_STUDIO_PARAMETER_DESCRIPTION paramDesc;
    desc->getParameterDescriptionByName(paramer, &paramDesc);
    FMOD_STUDIO_PARAMETER_ID surfaceID = paramDesc.id;
    instance->setParameterByID(surfaceID, value);

    // 播放
    instance->start();
    studioSystem->update();

    // 记录
    playMap[value] = instance;
}


void pauseMusicEvent(const char *path, const char *paramer, float value)
{
    FMOD::Studio::EventInstance *instance = playMap[value];
    instance->setVolume(0);
    instance->release();
    studioSystem->update();
}

void resumeMusicEvent(const char *path, const char *paramer, float value)
{
    FMOD::Studio::EventInstance *instance = playMap[value];
    instance->setVolume(1);
    instance->release();
    studioSystem->update();
}

void stopMusicEvent(const char *path, const char *paramer, float value)
{
    // 停止播放
    FMOD::Studio::EventInstance *instance = playMap[value];
    instance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
    instance->release();
    studioSystem->update();
    // 移除
    playMap.erase(value);
}

void playEffectEvent(const char *path)
{
    // 通过event创建实例
    FMOD::Studio::EventDescription *desc = NULL;
    studioSystem->getEvent(path, &desc);
    FMOD::Studio::EventInstance *instance = NULL;
    desc->createInstance(&instance);

    // 播放
    instance->start();
    instance->release();
    studioSystem->update();
}


extern "C"
{
    /*JNI_CALL_FUNCTION*/
    JNIEXPORT void Java_org_cocos2dx_javascript_AppActivity_loadBank(JNIEnv*env, jobject thiz)
    {
        loadBank();
    }
    JNIEXPORT void Java_org_cocos2dx_javascript_AppActivity_playMusicEvent(JNIEnv*env, jobject thiz, jstring path, jstring paramer, float value)
    {
        std::string pathStr = cocos2d::JniHelper::jstring2string(path);
        const char *cPath = pathStr.c_str();
        std::string paramerStr = cocos2d::JniHelper::jstring2string(paramer);
        const char *cParamer = paramerStr.c_str();
        playMusicEvent(cPath, cParamer, value);
    }
    JNIEXPORT void Java_org_cocos2dx_javascript_AppActivity_pauseMusicEvent(JNIEnv*env, jobject thiz, jstring path, jstring paramer, float value)
    {
        std::string pathStr = cocos2d::JniHelper::jstring2string(path);
        const char *cPath = pathStr.c_str();
        std::string paramerStr = cocos2d::JniHelper::jstring2string(paramer);
        const char *cParamer = paramerStr.c_str();
        pauseMusicEvent(cPath, cParamer, value);
    }
    JNIEXPORT void Java_org_cocos2dx_javascript_AppActivity_resumeMusicEvent(JNIEnv*env, jobject thiz, jstring path, jstring paramer, float value)
    {
        std::string pathStr = cocos2d::JniHelper::jstring2string(path);
        const char *cPath = pathStr.c_str();
        std::string paramerStr = cocos2d::JniHelper::jstring2string(paramer);
        const char *cParamer = paramerStr.c_str();
        resumeMusicEvent(cPath, cParamer, value);
    }
    JNIEXPORT void Java_org_cocos2dx_javascript_AppActivity_stopMusicEvent(JNIEnv*env, jobject thiz, jstring path, jstring paramer, float value)
    {
        std::string pathStr = cocos2d::JniHelper::jstring2string(path);
        const char *cPath = pathStr.c_str();
        std::string paramerStr = cocos2d::JniHelper::jstring2string(paramer);
        const char *cParamer = paramerStr.c_str();
        stopMusicEvent(cPath, cParamer, value);
    }
JNIEXPORT void Java_org_cocos2dx_javascript_AppActivity_playEffectEvent(JNIEnv*env, jobject thiz, jstring path)
{
    std::string pathStr = cocos2d::JniHelper::jstring2string(path);
    const char *cPath = pathStr.c_str();
    playEffectEvent(cPath);
}
}

