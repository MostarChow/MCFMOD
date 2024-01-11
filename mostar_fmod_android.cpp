
#include "AppDelegate.h"
#include "cocos2d.h"
#include <jni.h>

#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#include <map>

#include "fmod_android/inc/fmod.hpp"
#include "fmod_android/inc/fmod_studio.hpp"
#include "fmod_android/inc/fmod_errors.h"

#include <iostream>
#include <string>

#define LOG_TAG "main"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

FMOD::Studio::System *studioSystem;
// 实例化对象列表
std::map<std::string, FMOD::Studio::EventInstance *> playMap;
// 播放音乐列表
// {path,paramer,value : volume}
std::map<std::string, float> musicTask;
// 播放音效列表
// {path : 0}
std::map<std::string, float> effectTask;

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
    FMOD::Studio::Bank *ambBank = NULL;
    studioSystem->loadBankFile(GetMediaPath("amb.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &ambBank);

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
    std::string key = std::string(path) + "," + std::string(paramer) + "," + std::to_string(value);
    playMap[key] = instance;
    musicTask[key] = 1;
}


void pauseMusicEvent(const char *path, const char *paramer, float value)
{
    float volume = 0;
    std::string key = std::string(path) + "," + std::string(paramer) + "," + std::to_string(value);
    FMOD::Studio::EventInstance *instance = playMap[key];
    instance->setVolume(0);
    instance->release();
    studioSystem->update();
    // 记录播放任务
    musicTask[key] = volume;
}

void resumeMusicEvent(const char *path, const char *paramer, float value)
{
    float volume = 1;
    std::string key = std::string(path) + "," + std::string(paramer) + "," + std::to_string(value);
    FMOD::Studio::EventInstance *instance = playMap[key];
    instance->setVolume(1);
    instance->release();
    studioSystem->update();
    // 记录播放任务
    musicTask[key] = volume;
}

void stopMusicEvent(const char *path, const char *paramer, float value)
{
    // 停止播放
    std::string key = std::string(path) + "," + std::string(paramer) + "," + std::to_string(value);
    FMOD::Studio::EventInstance *instance = playMap[key];
    instance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
    instance->release();
    studioSystem->update();
    // 移除
    playMap.erase(key);
    musicTask.erase(key);
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

    // 记录
    std::string key = path;
    effectTask[key] = 0;
    playMap[key] = instance;
}

void stopEffectEvent(const char *path)
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
    // 移除
    std::string key = path;
    effectTask.erase(key);
    playMap.erase(key);
}

void pauseAll()
{
    for (auto it = playMap.begin(); it != playMap.end(); ++it)
    {
        FMOD::Studio::EventInstance *instance = it->second;
        instance->setVolume(0);
        instance->release();
        studioSystem->update();
    }
}

void resumeAll()
{
    // 恢复背景音乐
    for (auto it = musicTask.begin(); it != musicTask.end(); ++it)
    {
        float volume = it->second;
        if (volume > 0)
        {
            std::string key = it->first;
            FMOD::Studio::EventInstance *instance = playMap[key];
            instance->setVolume(1);
            instance->release();
            studioSystem->update();
        }
    }
    // 恢复音效
    for (auto it = effectTask.begin(); it != effectTask.end(); ++it)
    {
        std::string key = it->first;
        FMOD::Studio::EventInstance *instance = playMap[key];
        float volume = 1;
        instance->setVolume(volume);
        instance->release();
        studioSystem->update();
    }
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
    JNIEXPORT void Java_org_cocos2dx_javascript_AppActivity_stopEffectEvent(JNIEnv*env, jobject thiz, jstring path)
    {
        std::string pathStr = cocos2d::JniHelper::jstring2string(path);
        const char *cPath = pathStr.c_str();
        stopEffectEvent(cPath);
    }
    JNIEXPORT void Java_org_cocos2dx_javascript_AppActivity_pauseAll(JNIEnv*env, jobject thiz)
    {
        pauseAll();
    }
    JNIEXPORT void Java_org_cocos2dx_javascript_AppActivity_resumeAll(JNIEnv*env, jobject thiz)
    {
        resumeAll();
    }

}

