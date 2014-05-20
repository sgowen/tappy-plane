//
//  AppPrefs.h
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#pragma Local Settings

#define BEST_SCORE @"BEST_SCORE"

@interface AppPrefs : NSObject
{
    
}

+ (id)getInstance;

- (void)setBestScore:(int)score;

- (int)getBestScore;

@end