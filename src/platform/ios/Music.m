//
//  Music.m
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#import "Music.h"

@implementation Music

- (id)initWithMusicNamed:(NSString *)filename fromBundle:(NSBundle *)bundle;
{
    self = [super init];
    
    if (self)
    {
        NSString *sound_file = [bundle pathForResource:filename ofType:@"aifc"];
        if (sound_file)
        {
            NSURL *fileURL = [[NSURL alloc] initFileURLWithPath:sound_file];
            self.player = [[AVAudioPlayer alloc] initWithContentsOfURL:fileURL error:NULL];
            self.player.numberOfLoops = -1;
            self.player.delegate = self;
            [self.player prepareToPlay];
            
            NSLog(@"Loaded Music: %@", fileURL);
        }
    }
    
    return self;
}

#pragma <AVAudioPlayerDelegate> methods

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag
{
    NSLog(@"audioPlayerDidFinishPlaying");
}

- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError *)error
{
    NSLog(@"audioPlayerDecodeErrorDidOccur");
}

- (void)audioPlayerBeginInterruption:(AVAudioPlayer *)player
{
    NSLog(@"audioPlayerBeginInterruption");
}

- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player withOptions:(NSUInteger)flags NS_AVAILABLE_IOS(6_0)
{
    NSLog(@"audioPlayerEndInterruption withOptions");
}

- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player withFlags:(NSUInteger)flags NS_DEPRECATED_IOS(4_0, 6_0)
{
    NSLog(@"audioPlayerEndInterruption withFlags");
}

#pragma instance methods

- (void)play
{
    if(![self.player isPlaying])
    {
        [self.player play];
    }
}

- (void)pause
{
    if([self.player isPlaying])
    {
        [self.player pause];
    }
}

- (void)stop
{
    [self.player stop];
}

- (void)setLooping:(BOOL)isLooping
{
    if(isLooping)
    {
        self.player.numberOfLoops = -1;
    }
    else
    {
        self.player.numberOfLoops = 1;
    }
}

- (void)setVolume:(float)volume
{
    [self.player setVolume:volume];
}

- (bool)isValid
{
    return self.player && [self.player isPlaying];
}

- (void)dealloc
{
    [self stop];
    [self setPlayer:nil];
}

@end