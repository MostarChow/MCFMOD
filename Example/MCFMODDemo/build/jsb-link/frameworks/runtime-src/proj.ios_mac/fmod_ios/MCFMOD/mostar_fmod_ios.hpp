//
//  mostar_fmod_ios.hpp
//  MCFMOD-mobile
//
//  Created by Mostar on 2022/1/17.
//

#ifndef mostar_fmod_ios_hpp
#define mostar_fmod_ios_hpp

#include <stdio.h>

/**
 加载Bank
 */
void loadBank();

/**
 播放音乐Event
 */
void playMusicEvent(const char *path, const char *paramer, float value);

/**
 暂停播放音乐Event
 */
void pauseMusicEvent(const char *path, const char *paramer, float value);

/**
 继续播放音乐Event
 */
void resumeMusicEvent(const char *path, const char *paramer, float value);

/**
 停止播放音乐Event
 */
void stopMusicEvent(const char *path, const char *paramer, float value);

/**
 播放音效Event
 */
void playEffectEvent(const char *path);

/**
 停止播放音效Event
 */
void stopEffectEvent(const char *path);

#endif /* mostar_fmod_hpp */
