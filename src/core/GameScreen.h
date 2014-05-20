//
//  GameScreen.h
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "GameState.h"
#include "Rectangle.h"
#include "World.h"
#include "DynamicGameObject.h"
#include "PlaneDynamicGameObject.h"
#include "Glove.h"

#include <vector>
#include <memory>

class TouchEvent;
class Vector2D;
class GameButton;

class GameScreen
{
public:
	GameScreen();
    
    virtual void platformInit() = 0;
    
    virtual void touchToWorld(TouchEvent &touchEvent) = 0;
    
    virtual void platformResume() = 0;
    
    virtual void platformPause() = 0;

	void init();

	void onResume();
	
	void onPause();
	
	void update(float deltaTime, std::vector<TouchEvent> &touchEvents);

	virtual bool handleOnBackPressed() = 0;	
	
	int getState();
    
    void clearState();
    
    int getScore();
    
    void setBestScore(int bestScore);

protected:
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
    void updateWaiting(float deltaTime);
    
    void updateRunning(float deltaTime);
    
    void updateGameOver(float deltaTime);
    
    void updateInputWaiting(std::vector<TouchEvent> &touchEvents);
    
    void updateInputRunning(std::vector<TouchEvent> &touchEvents);
    
    void updateInputGameOver(std::vector<TouchEvent> &touchEvents);
};

#endif /* GAME_SCREEN_H */