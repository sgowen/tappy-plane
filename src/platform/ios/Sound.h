//
//  Sound.h
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#import <AudioToolbox/AudioServices.h>

@interface Sound : NSObject
{
@private
    NSString *fileName;
    SystemSoundID *soundID;
    int maxNumPlays;
    int soundIndex;
}

- (id) initWithSoundNamed:(NSString *)fileName fromBundle:(NSBundle *)bundle andMaxNumOfSimultaneousPlays:(int)mnsp;

- (void) play;

- (NSString *) getFileName;

@end