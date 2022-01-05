//
//  MCCommon.m
//  TestFmod-mobile
//
//  Created by Mostar on 2022/1/5.
//

#import "MCCommon.h"

#import <Foundation/Foundation.h>

const char *GetMediaPath(const char *fileName) {
    return [[NSString stringWithFormat:@"%@/media/%s", [[NSBundle mainBundle] resourcePath], fileName] UTF8String];
}
