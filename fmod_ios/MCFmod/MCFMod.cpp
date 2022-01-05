//
//  MCFMod.cpp
//  TestFmod-mobile
//
//  Created by Mostar on 2022/1/5.
//

#include "MCFMod.h"
#include "MCCommon.h"

#include "fmod.hpp"
#include "fmod_studio.hpp"
#include "fmod_errors.h"

FMOD::Studio::System *system = NULL;

void loadBank() {
    void *extradriverdata = NULL;
    // 创建studio对象
    FMOD::Studio::System::create(&system);
    // 创建core对象
    FMOD::System *coreSystem = NULL;
    system->getCoreSystem(&coreSystem);
    // 初始化studio
    system->initialize(2048, FMOD_INIT_NORMAL, FMOD_INIT_NORMAL, extradriverdata);
    // 加载bank
    FMOD::Studio::Bank *masterBank = NULL;
    system->loadBankFile(GetMediaPath("Master.bank"), FMOD_STUDIO_INIT_NORMAL, &masterBank);
    FMOD::Studio::Bank* stringsBank = NULL;
    system->loadBankFile(GetMediaPath("Master.strings.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
    FMOD::Studio::Bank *sfxBank = NULL;
    system->loadBankFile(GetMediaPath("SFX.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &sfxBank);
    FMOD::Studio::Bank *musicBank = NULL;
    system->loadBankFile(GetMediaPath("Music.bank"), FMOD_STUDIO_LOAD_BANK_NORMAL, &musicBank);
}

void playEvent(const char *path) {
    // 创建示例对象并加载
    FMOD::Studio::EventDescription *desc = NULL;
    system->getEvent(path, &desc);
    desc->loadSampleData();

    FMOD::Studio::EventInstance *instance = NULL;
    desc->createInstance(&instance);
    // 播放
    instance->start();
    instance->release();
    system->update();
}

void stopEvent(const char *path) {
    FMOD::Studio::EventDescription *desc = NULL;
    system->getEvent(path, &desc);
    // 获取实例对象
    FMOD::Studio::EventInstance *instance = NULL;
    int count = 0;
    desc->getInstanceCount(&count);
    desc->getInstanceList(&instance, count, &count);
    // 停止播放
    instance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
    system->update();
}
