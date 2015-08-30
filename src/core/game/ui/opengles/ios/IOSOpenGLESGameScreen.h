//
//  IOSOpenGLESGameScreen.h
//  tappyplane
//
//  Created by Stephen Gowen on 7/22/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__IOSOpenGLESGameScreen__
#define __tappyplane__IOSOpenGLESGameScreen__

#include "OpenGLESGameScreen.h"

class IOSOpenGLESGameScreen : public OpenGLESGameScreen
{
public:
    IOSOpenGLESGameScreen(int screenWidth, int screenHeight, int pointsWidth, int pointsHeight);
    
    virtual void touchToWorld(TouchEvent &touchEvent);
    
protected:
    int m_iPointsWidth;
    int m_iPointsHeight;
};

#endif /* defined(__tappyplane__IOSOpenGLESGameScreen__) */
