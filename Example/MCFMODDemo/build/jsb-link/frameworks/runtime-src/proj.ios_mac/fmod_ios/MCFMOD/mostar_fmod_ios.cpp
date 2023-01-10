//
//  mostar_fmod_ios.cpp
//  MCFMOD-mobile
//
//  Created by Mostar on 2022/1/17.
//

#include "mostar_fmod_ios.hpp"
#include "fmod.hpp"
#include "fmod_studio.hpp"
#include "mostar_common.h"

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>



FMOD::Studio::System *studioSystem = NULL;

// 音乐列表
std::map<float, FMOD::Studio::EventInstance *> playMap;

// 播放音乐列表
// {path,paramer,value : volume}
std::map<std::string, float> musicTask;
// 播放音效列表
// {path : 0}
std::map<std::string, float> effectTask;


void loadBank()
{
    // 创建studio对象
    FMOD::Studio::System::create(&studioSystem);
    // 创建core对象
    FMOD::System *coreSystem = NULL;
    studioSystem->getCoreSystem(&coreSystem);
    coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_SURROUND, 0);
    // 初始化studio
    void *extradriverdata = NULL;
    studioSystem->initialize(32, FMOD_INIT_NORMAL, FMOD_INIT_NORMAL, extradriverdata);
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
    playMap[value] = instance;
    // 记录播放任务
    std::string key = std::string(path) + "," + std::string(paramer) + "," + std::to_string(value);
    musicTask[key] = 1;
}


void pauseMusicEvent(const char *path, const char *paramer, float value)
{
    float volume = 0;
    FMOD::Studio::EventInstance *instance = playMap[value];
    instance->setVolume(volume);
    instance->release();
    studioSystem->update();
    // 记录播放任务
    std::string key = std::string(path) + "," + std::string(paramer) + "," + std::to_string(value);
    musicTask[key] = volume;
}

void resumeMusicEvent(const char *path, const char *paramer, float value)
{
    float volume = 1;
    FMOD::Studio::EventInstance *instance = playMap[value];
    instance->setVolume(volume);
    instance->release();
    studioSystem->update();
    // 记录播放任务
    std::string key = std::string(path) + "," + std::string(paramer) + "," + std::to_string(value);
    musicTask[key] = volume;
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
    
    // 记录
    std::string key = path;
    effectTask[key] = 0;
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
    for (auto it = playMap.begin(); it != playMap.end(); ++it)
    {
        FMOD::Studio::EventInstance *instance = it->second;
        instance->setVolume(1);
        instance->release();
        studioSystem->update();
    }
}

void stopAll()
{
    // 清空播放
    for (auto it = playMap.begin(); it != playMap.end();)
    {
        if (it->second) {
            FMOD::Studio::EventInstance *instance = it->second;
            instance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
            instance->release();
            studioSystem->update();
            playMap.erase(it++);
        } else {
            it++;
        }
    }
    playMap.clear();
}


void replayAll()
{
    // 卸载音效包
    studioSystem->unloadAll();
    // 重新加载
    loadBank();
    // 重新播放
    for (auto it = musicTask.begin(); it != musicTask.end(); ++it)
    {
        // 分割
        std::string key = it->first;
        std::vector<std::string> strings;
        std::istringstream input(key);
        std::string temp;
        while (getline(input, temp, ','))
        {
            strings.push_back(temp);
        }
        // 赋值
        const char *path = strings[0].c_str();
        const char *paramer = strings[1].c_str();
        float value = std::stof(strings[2]);
        float volume = it->second;
        
        // 播放
        
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
        instance->setVolume(volume);
        studioSystem->update();
        // 记录
        playMap[value] = instance;
        // 记录播放任务
        musicTask[key] = volume;
    }
    
    for (auto it = effectTask.begin(); it != effectTask.end(); ++it)
    {
        std::string key = it->first;
        const char *path = key.c_str();
        playEffectEvent(path);
    }
}

