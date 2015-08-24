//
//  DSGameScreen.h
//  tappyplane
//
//  Created by Stephen Gowen on 8/20/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__DSGameScreen__
#define __tappyplane__DSGameScreen__

#include "GameScreen.h"

class DSGameScreen : public GameScreen
{
public:
    DSGameScreen(int topScreenWidth, int topScreenHeight, int bottomScreenWidth, int bottomScreenHeight);

    virtual void init();

    virtual void touchToWorld(TouchEvent &touchEvent);

    virtual void platformResume();

    virtual void platformPause();

private:
    int m_iTopScreenWidth;
    int m_iTopScreenHeight;
    int m_iBottomScreenWidth;
    int m_iBottomScreenHeight;
};

#endif /* defined(__tappyplane__DSGameScreen__) */
