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
#include <vector>
#include <map>

FMOD::Studio::System *studioSystem = NULL;

std::map<float, FMOD::Studio::EventInstance *> playMap;

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
    FMOD::Studio::Bank *sfxBank = NULL;
    studioSystem->loadBankFile(GetMediaPath("SFX.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &sfxBank);
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
