//
//  GameScreen.h
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "GameState.h"
#include "Rectangle.h"
#include "World.h"
#include "PhysicalEntity.h"
#include "PlanePhysicalEntity.h"
#include "Glove.h"

#include <vector>
#include <memory>

#include "TouchType.h"

class TouchEvent;
class Vector2D;
class GameButton;
class Renderer;

class GameScreen
{
public:
    GameScreen();

    virtual void init();
    
    virtual void touchToWorld(TouchEvent &touchEvent) = 0;

    virtual void platformResume() = 0;

    virtual void platformPause() = 0;

    void onResume();

    void onPause();

    void update(float deltaTime);

    void render();

    int getState();

    void clearState();

    int getScore();

    void setBestScore(int bestScore);

    short getCurrentSoundId();

    void onTouch(Touch_Type type, float raw_touch_x, float raw_touch_y);

protected:
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Vector2D> m_touchPoint;
    std::unique_ptr<Glove> m_glove;
    std::unique_ptr<World> m_world;
    std::unique_ptr<GameButton> m_okButton;
    std::unique_ptr<GameButton> m_leaderboardsButton;
    Game_State m_gameState;
    int m_iDeviceScreenWidth;
    int m_iDeviceScreenHeight;
    int m_iScreenState;

    int m_iBestScore;

    // For background
    float m_fColor;
    float m_fTitleAlpha;

private:
    std::vector<TouchEvent> m_touchEvents;
    std::vector<TouchEvent> m_touchEventsPool;
    std::vector<TouchEvent> m_touchEventsBuffer;

    TouchEvent newTouchEvent();

    void addTouchEventForType(Touch_Type touchType, float x, float y);

    void updateWaiting(float deltaTime);

    void updateRunning(float deltaTime);

    void updateGameOver(float deltaTime);

    void updateInputWaiting(std::vector<TouchEvent> &touchEvents);

    void updateInputRunning(std::vector<TouchEvent> &touchEvents);

    void updateInputGameOver(std::vector<TouchEvent> &touchEvents);
};

#endif /* GAME_SCREEN_H */