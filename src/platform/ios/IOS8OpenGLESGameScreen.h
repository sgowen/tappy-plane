//
//  IOS8OpenGLESGameScreen.h
//  tappyplane
//
//  Created by Stephen Gowen on 7/22/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __nosfuratu__IOS8OpenGLESGameScreen__
#define __nosfuratu__IOS8OpenGLESGameScreen__

#include "IOSOpenGLESGameScreen.h"

class IOS8OpenGLESGameScreen : public IOSOpenGLESGameScreen
{
public:
    IOS8OpenGLESGameScreen(int screenWidth, int screenHeight, int pointsWidth, int pointsHeight);
    
    virtual void touchToWorld(TouchEvent &touchEvent);
};

#endif /* defined(__nosfuratu__IOS8OpenGLESGameScreen__) */
