//
//  Obstacle.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/11/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "Obstacle.h"
#include "PlaneDynamicGameObject.h"
#include "OverlapTester.h"
#include "Vector2D.h"
#include "Rectangle.h"
#include <random>

Obstacle::Obstacle(float x, float y, float width, float height, float speed, Environment_Type environmentType) : GameObject(x, y, width, height, 0)
{
    m_environmentType = environmentType;
    m_fSpeed = speed;
    
    reset(x);
}

bool Obstacle::update(float deltaTime, PlaneDynamicGameObject &plane)
{
    if(OverlapTester::doesRectangleOverlapTriangle(plane.getBounds(), *m_topBounds) || OverlapTester::doesRectangleOverlapTriangle(plane.getBounds(), *m_bottomBounds))
    {
        plane.hit();
    }
    
    getPosition().sub(m_fSpeed * deltaTime, 0);
    m_topBounds->update(getPosition().getX(), m_fTopBoundsLowestPointY, getPosition().getX() + getWidth() / 2, 32, getPosition().getX() - getWidth() / 2, 32);
    m_bottomBounds->update(getPosition().getX(), m_fBottomBoundsHighestPointY, getPosition().getX() + getWidth() / 2, 0, getPosition().getX() - getWidth() / 2, 0);
    
    if(getPosition().getX() < GAME_OFF_SCREEN_OBSTACLE_X)
    {
        getPosition().set(GAME_RESET_OBSTACLE_X, getPosition().getY());
        reset(GAME_RESET_OBSTACLE_X);
    }
    
    updateBounds();
    
    for (std::vector<std::unique_ptr<SpikeGameObject>>::iterator itr = m_spikes.begin(); itr != m_spikes.end(); itr++)
    {
        (*itr)->getPosition().set(getPosition().getX(), (*itr)->getPosition().getY());
    }
    
    if(!m_isPassed && plane.getPosition().getX() > getPosition().getX())
    {
        m_isPassed = true;
        return true;
    }
    
    return false;
}

std::vector<std::unique_ptr<SpikeGameObject>> & Obstacle::getSpikes()
{
    return m_spikes;
}

void Obstacle::reset(float x)
{
    m_isPassed = false;
    
    m_spikes.clear();
    
    float width = getWidth();
    
    int random_integer = rand() % 8;
	switch (random_integer)
	{
        case 0:
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x, 36.5f, width, 19, 180, m_environmentType)));
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x, 10.0f, width, 19,   0, m_environmentType)));
            
            m_fTopBoundsLowestPointY = 27;
            m_fBottomBoundsHighestPointY = 19.5f;
            break;
        case 1:
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x, 34.5f, width, 19, 180, m_environmentType)));
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x,  8.0f, width, 19,   0, m_environmentType)));
            
            m_fTopBoundsLowestPointY = 25;
            m_fBottomBoundsHighestPointY = 17.5f;
            break;
        case 2:
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x, 32.5f, width, 19, 180, m_environmentType)));
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x,  6.0f, width, 19,   0, m_environmentType)));
            
            m_fTopBoundsLowestPointY = 23;
            m_fBottomBoundsHighestPointY = 15.5f;
            break;
        case 3:
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x, 30.5f, width, 19, 180, m_environmentType)));
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x,  4.0f, width, 19,   0, m_environmentType)));
            
            m_fTopBoundsLowestPointY = 21;
            m_fBottomBoundsHighestPointY = 13.5f;
            break;
        case 4:
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x, 28.5f, width, 19, 180, m_environmentType)));
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x,  2.0f, width, 19,   0, m_environmentType)));
            
            m_fTopBoundsLowestPointY = 19;
            m_fBottomBoundsHighestPointY = 11.5f;
            break;
        case 5:
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x, 26.5f, width, 19, 180, m_environmentType)));
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x,  0.0f, width, 19,   0, m_environmentType)));
            
            m_fTopBoundsLowestPointY = 17;
            m_fBottomBoundsHighestPointY = 9.5f;
            break;
        case 6:
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x, 24.5f, width, 19, 180, m_environmentType)));
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x, -2.0f, width, 19,   0, m_environmentType)));
            
            m_fTopBoundsLowestPointY = 15;
            m_fBottomBoundsHighestPointY = 7.5f;
            break;
        case 7:
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x, 23.0f, width, 19, 180, m_environmentType)));
            m_spikes.push_back(std::unique_ptr<SpikeGameObject>(new SpikeGameObject(x, -4.0f, width, 19,   0, m_environmentType)));
            
            m_fTopBoundsLowestPointY = 14;
            m_fBottomBoundsHighestPointY = 6.5f;
            break;
	}
    
    m_topBounds = std::unique_ptr<Triangle>(new Triangle(x, m_fTopBoundsLowestPointY, x + width / 2, 32, x - width / 2, 32));
    m_bottomBounds = std::unique_ptr<Triangle>(new Triangle(x, m_fBottomBoundsHighestPointY, x + width / 2, 0, x - width / 2, 0));
}