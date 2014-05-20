//
//  OpenGLESGameScreen.h
//  tappyplane
//
//  Created by Stephen Gowen on 1/31/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __tappyplane__OpenGLESGameScreen__
#define __tappyplane__OpenGLESGameScreen__

#include "GameScreen.h"

class OpenGLESRenderer;

class OpenGLESGameScreen : public GameScreen
{
public:
    OpenGLESGameScreen();
    
    virtual void platformInit();
    
    virtual void touchToWorld(TouchEvent &touchEvent);
    
    virtual void platformResume();
    
    virtual void platformPause();
    
    virtual bool handleOnBackPressed();
    
    void onSurfaceCreated(int deviceScreenWidth, int deviceScreenHeight);
    
	void onSurfaceChanged(int deviceScreenWidth, int deviceScreenHeight);
    
	void setDpDimensions(int dpWidth, int dpHeight);
    
    void present();

private:
    std::unique_ptr<OpenGLESRenderer> m_renderer;
    int m_iDeviceScreenDpWidth;
    int m_iDeviceScreenDpHeight;
};

#endif /* defined(__tappyplane__OpenGLESGameScreen__) */
