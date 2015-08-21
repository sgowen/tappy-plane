//
//  GGDDeviceUtil.m
//  tappyplane
//
//  Created by Stephen Gowen on 9/8/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#import "GGDDeviceUtil.h"

@implementation GGDDeviceUtil

+ (bool)isIPhoneFiveScreen
{
    if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
    {
        CGSize result = [[UIScreen mainScreen] bounds].size;
        CGFloat scale = [UIScreen mainScreen].scale;
        result = CGSizeMake(result.width * scale, result.height * scale);
        
        if(result.height == 1136)
        {
            return true;
        }
    }
    
    return false;
}

+ (bool)isIPadScreen
{
    if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
    {
        return true;
    }
    
    return false;
}

+ (bool)isSimulator
{
    NSString *model = [[UIDevice currentDevice] model];
    
    return [model isEqualToString:@"iPhone Simulator"];
}

+ (bool)isRunningiOS6OrAbove
{
    return SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"6.0");
}

+ (bool)isRunningiOS7OrAbove
{
    return SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"7.0");
}

+ (bool)isDeviceInLandscapeMode
{
    UIInterfaceOrientation orientation = [UIApplication sharedApplication].statusBarOrientation;
    
    if(orientation == 0)
    {
        return false;
    }
    else if(orientation == UIInterfaceOrientationPortrait)
    {
        return false;
    }
    else if(orientation == UIInterfaceOrientationPortraitUpsideDown)
    {
        return false;
    }
    else if(orientation == UIInterfaceOrientationLandscapeLeft)
    {
        return true;
    }
    else if(orientation == UIInterfaceOrientationLandscapeRight)
    {
        return true;
    }
    else
    {
        return false;
    }
}

@end