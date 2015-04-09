//
//  GameListener.h
//  tappyplane
//
//  Created by Stephen Gowen on 5/28/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__GameListener__
#define __tappyplane__GameListener__

#ifdef GGD_DIRECT_3D
#define strdup _strdup
#endif

#include <vector>

class PlayerDynamicGameObject;

class GameListener
{
public:
    static GameListener * getInstance();

    void playSound(short soundId);
    
private:
    GameListener();
};

#endif /* defined(__tappyplane__GameListener__) */