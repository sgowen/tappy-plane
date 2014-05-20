//
//  AppPrefs.m
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#import "AppPrefs.h"

@implementation AppPrefs

static AppPrefs *instance = nil;

+ (id)getInstance
{
    if(instance == nil)
    {
        instance = [[AppPrefs alloc] init];
    }
    
	return instance;
}

- (void)setBestScore:(int)score
{
    [self setInt:score forKey:BEST_SCORE];
}

- (int)getBestScore
{
    return [self getInt:BEST_SCORE];
}

#pragma private methods

- (void)setString:(NSString *)value forKey:(NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults setObject:value forKey:key];
    [userDefaults synchronize];
}

- (void)setBool:(BOOL)value forKey:(NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults setBool:value forKey:key];
    [userDefaults synchronize];
}

- (void)setInt:(int)value forKey:(NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults setInteger:value forKey:key];
    [userDefaults synchronize];
}

- (NSString *)getString:(NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    return [userDefaults objectForKey:key];
}

- (BOOL)getBool:(NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    return [userDefaults boolForKey:key];
}

- (int)getInt:(NSString *)key
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    return [userDefaults integerForKey:key];
}

@end
