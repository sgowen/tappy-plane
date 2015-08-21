//
//  OpenGLESGameScreen.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__OpenGLESGameScreen__
#define __tappyplane__OpenGLESGameScreen__

#include "GameScreen.h"

class OpenGLESRenderer;

class OpenGLESGameScreen : public GameScreen
{
public:
    OpenGLESGameScreen();
    
    void onSurfaceCreated(int deviceScreenWidth, int deviceScreenHeight);
    
    void onSurfaceChanged(int deviceScreenWidth, int deviceScreenHeight);
    
    virtual void platformResume();
    
    virtual void platformPause();
};

#endif /* defined(__tappyplane__OpenGLESGameScreen__) */
