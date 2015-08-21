//
//  GGDDeviceUtil.h
//  tappyplane
//
//  Created by Stephen Gowen on 9/8/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#define SYSTEM_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

@interface GGDDeviceUtil : NSObject
{
    
}

+ (bool)isIPhoneFiveScreen;

+ (bool)isIPadScreen;

+ (bool)isSimulator;

+ (bool)isRunningiOS6OrAbove;

+ (bool)isRunningiOS7OrAbove;

+ (bool)isDeviceInLandscapeMode;

@end
