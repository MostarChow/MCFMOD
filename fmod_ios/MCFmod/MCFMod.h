//
//  MCFMod.hpp
//  TestFmod-mobile
//
//  Created by Mostar on 2022/1/5.
//

#ifndef MCFMod_hpp
#define MCFMod_hpp

#include <stdio.h>

/**
 加载Bank文件
 (在AppDelegate::applicationDidFinishLaunching调用)
 */
void loadBank();

/**
 播放Event
 */
void playEvent(const char *path);

/**
 停止播放Event
 */
void stopEvent(const char *path);

#endif /* MCFMod_hpp */
