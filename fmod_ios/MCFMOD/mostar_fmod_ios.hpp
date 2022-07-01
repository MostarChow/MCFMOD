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
 播放Event
 */
void playEvent(const char *path);

/**
 暂停播放Event
 */
void pauseEvent(const char *path);

/**
 继续播放Event
 */
void resumeEvent(const char *path);

/**
 停止播放Event
 */
void stopEvent(const char *path);

#endif /* mostar_fmod_hpp */
