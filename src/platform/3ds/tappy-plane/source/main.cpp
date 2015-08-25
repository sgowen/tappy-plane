//
//  main.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 8/20/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include <string.h>

#include <3ds.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "DSGameScreen.h"
#include "Vector2D.h"
#include "TouchEvent.h"
#include "Vector2D.h"
#include "Rectangle.h"
#include "Assets.h"
#include "OverlapTester.h"
#include "Renderer.h"
#include "LineBatcher.h"
#include "RectangleBatcher.h"
#include "Triangle.h"
#include "Font.h"
#include "SpriteBatcher.h"
#include "LineBatcher.h"
#include "CircleBatcher.h"
#include "Rectangle.h"
#include "Circle.h"
#include "GameButton.h"
#include "SpikePhysicalEntity.h"
#include "ResourceConstants.h"

extern "C"
{
#include "sfx.h"
#include "filesystem.h"
}

#define TICKS_PER_SEC (268123480)

int main(int argc, char** argv)
{
    DSGameScreen gameScreen = DSGameScreen(400, 240, 320, 240);

    u64 lastTick = svcGetSystemTick();

    touchPosition lastTouchPosition = {0, 0};

    // Main loop
    while (aptMainLoop())
    {
        u64 newTick = svcGetSystemTick();
        float deltaTime = ((float) (newTick - lastTick)) / TICKS_PER_SEC;
        lastTick = newTick;

        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
        {
            break; // break in order to return to hbmenu
        }

        touchPosition touch;

        //Read the touch screen coordinates
        hidTouchRead(&touch);

        if (lastTouchPosition.px == 0 && lastTouchPosition.py == 0)
        {
            if (touch.px != 0 && touch.py != 0)
            {
                gameScreen.onTouch(Touch_Type::DOWN, touch.px, touch.py);
            }
        }
        else
        {
            if (touch.px == 0 && touch.py == 0)
            {
                gameScreen.onTouch(Touch_Type::UP, lastTouchPosition.px, lastTouchPosition.py);
            }
            else
            {
                gameScreen.onTouch(Touch_Type::DRAGGED, touch.px, touch.py);
            }
        }

        lastTouchPosition.px = touch.px;
        lastTouchPosition.py = touch.py;

        gameScreen.update(deltaTime);

        gameScreen.render();

        // Handle Sound for this frame
        short soundId;
        while ((soundId = gameScreen.getCurrentSoundId()) > 0)
        {
            switch (soundId)
            {
            case ASCEND_SOUND:
                // TODO, play sound
                break;
            case SCORE_SOUND:
                // TODO, play sound
                break;
            case HIT_SOUND:
                // TODO, play sound
                break;
            case LAND_SOUND:
                // TODO, play sound
                break;
            default:
                break;
            }
        }
    }

    gameScreen.exit();

    return 0;
}