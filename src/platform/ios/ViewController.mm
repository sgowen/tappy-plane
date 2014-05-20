//
//  ViewController.mm
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#import "ViewController.h"
#include "game.h"
#include "Assets.h"
#include "Music.h"
#include "Sound.h"
#include "AppPrefs.h"

@interface ViewController ()
{
    // Empty
}

@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) Sound *ascendSound;
@property (strong, nonatomic) Sound *scoreSound;
@property (strong, nonatomic) Sound *hitSound;
@property (strong, nonatomic) Sound *landSound;

- (void)setupGL;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    
    if (!self.context)
    {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.userInteractionEnabled = YES;
    
    [self setupGL];
    
    self.ascendSound = [[Sound alloc] initWithSoundNamed:@"ascend.caf" fromBundle:[NSBundle mainBundle] andMaxNumOfSimultaneousPlays:3];
    self.scoreSound = [[Sound alloc] initWithSoundNamed:@"score.caf" fromBundle:[NSBundle mainBundle] andMaxNumOfSimultaneousPlays:2];
    self.hitSound = [[Sound alloc] initWithSoundNamed:@"hit.caf" fromBundle:[NSBundle mainBundle] andMaxNumOfSimultaneousPlays:1];
    self.landSound = [[Sound alloc] initWithSoundNamed:@"land.caf" fromBundle:[NSBundle mainBundle] andMaxNumOfSimultaneousPlays:1];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onPause)
                                                 name:UIApplicationWillResignActiveNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onResume)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView: [UIApplication sharedApplication].keyWindow];
    on_touch_down(pos.x, pos.y);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView: [UIApplication sharedApplication].keyWindow];
    on_touch_dragged(pos.x, pos.y);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView: [UIApplication sharedApplication].keyWindow];
    on_touch_up(pos.x, pos.y);
}

#pragma GLKView and GLKViewController delegate methods

- (void)update
{
    int gameState = get_state();
    switch (gameState)
    {
        case 0:
            update(self.timeSinceLastUpdate);
            break;
        case 1:
            init();
            break;
        case 2:
            [self dismissViewControllerAnimated:true completion:nil];
            break;
        case 3:
            clear_state();
            [self handleFinalScore];
            break;
        case 4:
            clear_state();
            // TODO, show Leaderboards here if you want
            break;
        default:
            break;
    }
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    present();
    [self handleSoundId:get_current_sound_id()];
}

#pragma private methods

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    self.preferredFramesPerSecond = 60;
    
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    CGFloat screenScale = [[UIScreen mainScreen] scale];
    CGSize screenSize = CGSizeMake(screenBounds.size.width * screenScale, screenBounds.size.height * screenScale);
    
    CGSize newSize = CGSizeMake(screenSize.width, screenSize.height);
    newSize.width = roundf(newSize.width);
	newSize.height = roundf(newSize.height);
    
    NSLog(@"dimension %f x %f", newSize.width, newSize.height);
    
    init();
    on_surface_created(newSize.width, newSize.height);
    on_surface_changed(newSize.width, newSize.height, [UIScreen mainScreen].applicationFrame.size.width, [UIScreen mainScreen].applicationFrame.size.height);
    on_resume();
}

- (void)handleFinalScore
{
    int score = get_score();
    int bestScore = [[AppPrefs getInstance] getBestScore];
    
    if(score > bestScore)
    {
        [[AppPrefs getInstance] setBestScore:score];
    }
    
    set_best_score([[AppPrefs getInstance] getBestScore]);
}

- (void)handleSoundId:(short)soundId
{
    switch (soundId)
    {
        case ASCEND_SOUND:
            [self.ascendSound play];
            break;
        case SCORE_SOUND:
            [self.scoreSound play];
            break;
        case HIT_SOUND:
            [self.hitSound play];
            break;
        case LAND_SOUND:
            [self.landSound play];
            break;
        default:
            break;
    }
}

- (void)onResume
{
    on_resume();
}

- (void)onPause
{
    on_pause();
}

@end
