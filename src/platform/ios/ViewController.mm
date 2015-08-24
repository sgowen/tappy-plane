//
//  ViewController.mm
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#import "ViewController.h"
#import "GGDDeviceUtil.h"
#import "AppPrefs.h"
#import "Logger.h"

// C++
#include "IOSOpenGLESGameScreen.h"
#include "IOS8OpenGLESGameScreen.h"
#include "Sound.h"
#include "ResourceConstants.h"
#include "ScreenState.h"

@interface ViewController ()
{
    IOSOpenGLESGameScreen *gameScreen;
}

@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) Sound *ascendSound;
@property (strong, nonatomic) Sound *scoreSound;
@property (strong, nonatomic) Sound *hitSound;
@property (strong, nonatomic) Sound *landSound;

@end

@implementation ViewController

static Logger *logger = nil;
static bool isRunningiOS8 = false;

+ (void)initialize
{
    logger = [[Logger alloc] initWithClass:[ViewController class]];
    isRunningiOS8 = SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"8.0");
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (!self.context)
    {
        [logger error:@"Failed to create ES context"];
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.userInteractionEnabled = YES;
    [view setMultipleTouchEnabled:YES];
    
    self.preferredFramesPerSecond = 60;
    
    self.ascendSound = [[Sound alloc] initWithSoundNamed:@"ascend.caf" fromBundle:[NSBundle mainBundle] andMaxNumOfSimultaneousPlays:3];
    self.scoreSound = [[Sound alloc] initWithSoundNamed:@"score.caf" fromBundle:[NSBundle mainBundle] andMaxNumOfSimultaneousPlays:2];
    self.hitSound = [[Sound alloc] initWithSoundNamed:@"hit.caf" fromBundle:[NSBundle mainBundle] andMaxNumOfSimultaneousPlays:1];
    self.landSound = [[Sound alloc] initWithSoundNamed:@"land.caf" fromBundle:[NSBundle mainBundle] andMaxNumOfSimultaneousPlays:1];
    
    [EAGLContext setCurrentContext:self.context];
    
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    CGFloat screenScale = [[UIScreen mainScreen] scale];
    CGSize screenSize = CGSizeMake(screenBounds.size.width * screenScale, screenBounds.size.height * screenScale);
    
    CGSize newSize = CGSizeMake(screenSize.width, screenSize.height);
    newSize.width = roundf(newSize.width);
    newSize.height = roundf(newSize.height);
    
    [logger debug:[NSString stringWithFormat:@"dimension %f x %f", newSize.width, newSize.height]];
    
    [view bindDrawable];
    
    if(isRunningiOS8)
    {
        [logger debug:@"Instantiating IOS8OpenGLESGameScreen"];
        gameScreen = new IOS8OpenGLESGameScreen(MIN(newSize.width, newSize.height), MAX(newSize.width, newSize.height), [UIScreen mainScreen].applicationFrame.size.width, [UIScreen mainScreen].applicationFrame.size.height);
    }
    else
    {
        [logger debug:@"Instantiating IOSOpenGLESGameScreen"];
        gameScreen = new IOSOpenGLESGameScreen(MIN(newSize.width, newSize.height), MAX(newSize.width, newSize.height), [UIScreen mainScreen].applicationFrame.size.width, [UIScreen mainScreen].applicationFrame.size.height);
    }
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onPause)
                                                 name:UIApplicationWillResignActiveNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onResume)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    [self onPause];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView: [UIApplication sharedApplication].keyWindow];
    gameScreen->onTouch(DOWN, pos.x, pos.y);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView: [UIApplication sharedApplication].keyWindow];
    gameScreen->onTouch(DRAGGED, pos.x, pos.y);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView: [UIApplication sharedApplication].keyWindow];
    gameScreen->onTouch(UP, pos.x, pos.y);
}

#pragma mark <GLKViewControllerDelegate>

- (void)update
{
    int screenState = gameScreen->getState();
    switch (screenState)
    {
        case SCREEN_STATE_NORMAL:
            gameScreen->update(self.timeSinceLastUpdate);
            break;
        case SCREEN_STATE_RESET:
            gameScreen->init();
            break;
        case SCREEN_STATE_EXIT:
            [self dismissViewControllerAnimated:NO completion:nil];
            break;
        case SCREEN_STATE_GAME_OVER:
            gameScreen->clearState();
            [self handleFinalScore];
            break;
        case SCREEN_STATE_LEADERBOARDS:
            gameScreen->clearState();
            // TODO, show Leaderboards here if you want
            break;
        default:
            break;
    }
}

#pragma mark <GLKViewDelegate>

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    gameScreen->render();
    [self handleSound];
}

#pragma mark <Private>

- (void)handleFinalScore
{
    int score = gameScreen->getScore();
    int bestScore = [[AppPrefs getInstance] getBestScore];
    
    if(score > bestScore)
    {
        [[AppPrefs getInstance] setBestScore:score];
    }
    
    gameScreen->setBestScore([[AppPrefs getInstance] getBestScore]);
}

- (void)handleSound
{
    short soundId;
    while ((soundId = gameScreen->getCurrentSoundId()) > 0)
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
}

- (void)onResume
{
    gameScreen->onResume();
}

- (void)onPause
{
    gameScreen->onPause();
}

@end