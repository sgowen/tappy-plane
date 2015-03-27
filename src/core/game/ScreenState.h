//
//  ScreenState.h
//  tappyplane
//
//  Created by Stephen Gowen on 11/18/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef tappyplane_ScreenState_h
#define tappyplane_ScreenState_h

/// Screen States are used to indicate to the outer layer (Java, Obj-C, C#)
/// that some interesting shit has happened on the C++ layer

#define SCREEN_STATE_NORMAL 0
#define SCREEN_STATE_RESET 1
#define SCREEN_STATE_EXIT 2
#define SCREEN_STATE_GAME_OVER 3
#define SCREEN_STATE_LEADERBOARDS 4

#endif