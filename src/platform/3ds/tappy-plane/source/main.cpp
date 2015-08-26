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

#include <memory>

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
#include "DSSpriteBatcher.h"
#include "TextureWrapper.h"
#include "TopScreenRenderer.h"
#include "GameConstants.h"

extern "C"
{
#include "sfx.h"
#include "filesystem.h"
}

#define TICKS_PER_SEC (268123480)

int main(int argc, char** argv)
{
    filesystemInit(argc, argv);

    initSound();

    SFX_s* ascendSFX = createSFX("ascend.raw", SOUND_FORMAT_16BIT);
    SFX_s* hitSFX = createSFX("hit.raw", SOUND_FORMAT_16BIT);
    SFX_s* landSFX = createSFX("land.raw", SOUND_FORMAT_16BIT);
    SFX_s* scoreSFX = createSFX("score.raw", SOUND_FORMAT_16BIT);

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

        short soundId;
        while ((soundId = gameScreen.getCurrentSoundId()) > 0)
        {
            switch (soundId)
            {
            case ASCEND_SOUND:
                playSFX(ascendSFX);
                break;
            case SCORE_SOUND:
                playSFX(scoreSFX);
                break;
            case HIT_SOUND:
                playSFX(hitSFX);
                break;
            case LAND_SOUND:
                playSFX(landSFX);
                break;
            default:
                break;
            }
        }
    }

    exitSound();

    gameScreen.exit();

    return 0;
}