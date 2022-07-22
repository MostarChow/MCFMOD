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

FMOD::Studio::System *studioSystem = NULL;

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

void pauseEvent(const char *path)
{
    FMOD::Studio::EventDescription *desc = NULL;
    studioSystem->getEvent(path, &desc);
    // 获取实例对象
    FMOD::Studio::EventInstance *instance = NULL;
    int count = 0;
    desc->getInstanceCount(&count);
    desc->getInstanceList(&instance, count, &count);
    // 暂停播放
    instance->setPaused(true);
    studioSystem->update();
}

void resumeEvent(const char *path)
{
    FMOD::Studio::EventDescription *desc = NULL;
    studioSystem->getEvent(path, &desc);
    // 获取实例对象
    FMOD::Studio::EventInstance *instance = NULL;
    int count = 0;
    desc->getInstanceCount(&count);
    desc->getInstanceList(&instance, count, &count);
    // 继续播放
    instance->setPaused(false);
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
