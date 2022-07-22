//
//  mostar_common.m
//  MCFMOD-mobile
//
//  Created by Mostar on 2022/1/17.
//

#import "mostar_common.h"

@implementation mostar_common

const char *GetMediaPath(const char *fileName) {
    return [[NSString stringWithFormat:@"%@/media/%s", [[NSBundle mainBundle] resourcePath], fileName] UTF8String];
}


@end
