//
//  Sound.m
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#import "Sound.h"

@implementation Sound

- (id)initWithSoundNamed:(NSString *)fn fromBundle:(NSBundle *)bundle andMaxNumOfSimultaneousPlays:(int)mnsp;
{
    fileName = fn;
    soundID = malloc(sizeof(SystemSoundID) * mnsp);
    maxNumPlays = mnsp;
    soundIndex = 0;
    
    if ((self = [super init]))
    {
        NSURL *fileURL = [bundle URLForResource:fileName withExtension:nil];
        bool success = true;
        
        if (fileURL != nil)
        {
            for (int i = 0; i < mnsp; i++)
            {
                SystemSoundID theSoundID;
                OSStatus error = AudioServicesCreateSystemSoundID((__bridge CFURLRef)fileURL, &theSoundID);
                
                if (error == kAudioServicesNoError)
                {
                    soundID[i] = theSoundID;
                }
                else
                {
                    NSLog(@"Error Loading Sound: %@", fileURL);
                    success = false;
                }
            }
            
            if(success)
            {
                NSLog(@"Loaded Sound: %@", fileURL);
            }
        }
    }
    
    return self;
}

- (void)dealloc
{
    for (int i = 0; i < maxNumPlays; i++)
    {
        AudioServicesDisposeSystemSoundID(soundID[i]);
    }
}

- (void)play
{
    if(soundIndex >= maxNumPlays)
    {
        soundIndex = 0;
    }
    
    AudioServicesPlaySystemSound(soundID[soundIndex++]);
}

- (NSString *) getFileName
{
    return fileName;
}

@end