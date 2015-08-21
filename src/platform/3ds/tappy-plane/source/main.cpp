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

#define TICKS_PER_SEC (268123480)

int main()
{
    gfxInitDefault();

    DSGameScreen gameScreen = DSGameScreen();

    u64 lastTick = svcGetSystemTick();

    // Main loop
    while (aptMainLoop())
    {
        u64 newTick = svcGetSystemTick();
        float deltaTime = ((float) (newTick - lastTick)) / TICKS_PER_SEC;
        lastTick = newTick;

        gspWaitForVBlank();
        hidScanInput();

        gameScreen.update(deltaTime);
        gameScreen.render();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
        {
            break; // break in order to return to hbmenu
        }
        else if (kDown & KEY_A)
        {
            gameScreen.onTouch(Touch_Type::DOWN, 0, 0);
            gameScreen.onTouch(Touch_Type::UP, 0, 0);
        }

        // Flush and swap framebuffers
        gfxFlushBuffers();
        gfxSwapBuffers();
    }

    gfxExit();

    return 0;
}
