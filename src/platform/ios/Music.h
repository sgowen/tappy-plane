//
//  Music.h
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>

@interface Music : NSObject <AVAudioPlayerDelegate>
{
    
}

@property (retain, nonatomic) AVAudioPlayer *player;

- (id)initWithMusicNamed:(NSString *)filename fromBundle:(NSBundle *)bundle;

- (void)play;

- (void)pause;

- (void)stop;

- (void)setLooping:(BOOL)isLooping;

- (void)setVolume:(float)volume;

- (bool)isValid;

- (void)dealloc;

@end