//
//  GameListener.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 5/28/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "GameListener.h"
#include "Assets.h"

GameListener * GameListener::getInstance()
{
    static GameListener *gameListener = new GameListener();
    return gameListener;
}

void GameListener::playSound(short soundId)
{
    Assets::getInstance()->addSoundIdToPlayQueue(soundId);
}

GameListener::GameListener()
{
    // Hide Constructor for Singleton
}