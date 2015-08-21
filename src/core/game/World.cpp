//
//  World.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/10/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#define GAME_SPEED 8

#include "GameConstants.h"
#include "World.h"
#include "Rectangle.h"
#include "Vector2D.h"
#include "PlanePhysicalEntity.h"
#include "TouchEvent.h"
#include "GameListener.h"
#include "Obstacle.h"
#include "Triangle.h"
#include "SpikePhysicalEntity.h"
#include "Line.h"
#include "ResourceConstants.h"
#include <random>

World::World()
{
    m_plane = std::unique_ptr<PlanePhysicalEntity>(new PlanePhysicalEntity(SCREEN_WIDTH / 8 * 3, SCREEN_HEIGHT / 2, 3.95f, 3.25f));
    
    int randomInt = rand() % 4;
    m_environmentType = randomInt == 0 ? GRASS : randomInt == 1 ? ROCK : randomInt == 2 ? SNOW : ICE;
    
    m_obstacles.push_back(std::unique_ptr<Obstacle>(new Obstacle(GAME_RESET_OBSTACLE_X, SCREEN_HEIGHT / 2, 8.55f, SCREEN_HEIGHT, GAME_SPEED, m_environmentType)));
    m_obstacles.push_back(std::unique_ptr<Obstacle>(new Obstacle(SCREEN_WIDTH / 8 * 20, SCREEN_HEIGHT / 2, 8.55f, SCREEN_HEIGHT, GAME_SPEED, m_environmentType)));
    m_obstacles.push_back(std::unique_ptr<Obstacle>(new Obstacle(SCREEN_WIDTH / 8 * 25, SCREEN_HEIGHT / 2, 8.55f, SCREEN_HEIGHT, GAME_SPEED, m_environmentType)));
    m_obstacles.push_back(std::unique_ptr<Obstacle>(new Obstacle(SCREEN_WIDTH / 8 * 30, SCREEN_HEIGHT / 2, 8.55f, SCREEN_HEIGHT, GAME_SPEED, m_environmentType)));
    m_obstacles.push_back(std::unique_ptr<Obstacle>(new Obstacle(SCREEN_WIDTH / 8 * 35, SCREEN_HEIGHT / 2, 8.55f, SCREEN_HEIGHT, GAME_SPEED, m_environmentType)));
    m_obstacles.push_back(std::unique_ptr<Obstacle>(new Obstacle(SCREEN_WIDTH / 8 * 40, SCREEN_HEIGHT / 2, 8.55f, SCREEN_HEIGHT, GAME_SPEED, m_environmentType)));
    
    m_foregroundLeft = std::unique_ptr<PhysicalEntity>(new PhysicalEntity(SCREEN_WIDTH_1_2, GAME_WORLD_BASE_1_2, SCREEN_WIDTH, GAME_WORLD_BASE, 0));
    m_foregroundRight = std::unique_ptr<PhysicalEntity>(new PhysicalEntity(SCREEN_WIDTH_3_2, GAME_WORLD_BASE_1_2, SCREEN_WIDTH, GAME_WORLD_BASE, 0));
    
    m_iScore = 0;
}

void World::startGame()
{
    m_plane->startFlying();
}

void World::update(float deltaTime)
{
    float shiftX = deltaTime * GAME_SPEED;
    
    m_plane->update(deltaTime, shiftX);
    
    if(m_plane->isHit() || m_plane->isDead())
    {
        return;
    }
    
    if(m_plane->isFlying())
    {
        for (std::vector<std::unique_ptr<Obstacle>>::iterator itr = m_obstacles.begin(); itr != m_obstacles.end(); itr++)
        {
            if((*itr)->update(deltaTime, *m_plane))
            {
                GameListener::getInstance()->playSound(SCORE_SOUND);
                m_iScore++;
            }
        }
    }
    
    if(m_foregroundLeft->getPosition().getX() < m_foregroundRight->getPosition().getX())
    {
        m_foregroundLeft->getPosition().sub(shiftX, 0);
        m_foregroundRight->getPosition().set(m_foregroundLeft->getPosition().getX() + SCREEN_WIDTH, m_foregroundRight->getPosition().getY());
    }
    else
    {
        m_foregroundRight->getPosition().sub(shiftX, 0);
        m_foregroundLeft->getPosition().set(m_foregroundRight->getPosition().getX() + SCREEN_WIDTH, m_foregroundLeft->getPosition().getY());
    }
    
    if(m_foregroundLeft->getPosition().getX() < -SCREEN_WIDTH_1_2)
    {
        m_foregroundLeft->getPosition().set(SCREEN_WIDTH_3_2, m_foregroundLeft->getPosition().getY());
        m_foregroundRight->getPosition().set(SCREEN_WIDTH_1_2, m_foregroundRight->getPosition().getY());
    }
    else if(m_foregroundRight->getPosition().getX() < -SCREEN_WIDTH_1_2)
    {
        m_foregroundRight->getPosition().set(SCREEN_WIDTH_3_2, m_foregroundRight->getPosition().getY());
        m_foregroundLeft->getPosition().set(SCREEN_WIDTH_1_2, m_foregroundLeft->getPosition().getY());
    }
    
    m_foregroundLeft->updateBounds();
    m_foregroundRight->updateBounds();
}

void World::handleTouchUp(TouchEvent &touchEvent)
{
    m_plane->ascend();
}

std::vector<std::unique_ptr<Obstacle>> & World::getObstacles()
{
    return m_obstacles;
}

PhysicalEntity & World::getForegroundLeft()
{
    return *m_foregroundLeft;
}

PhysicalEntity & World::getForegroundRight()
{
    return *m_foregroundRight;
}

PlanePhysicalEntity & World::getPlane()
{
    return *m_plane;
}

Environment_Type World::getEnvironmentType()
{
    return m_environmentType;
}

int World::getScore()
{
    return m_iScore;
}

bool World::isGameOver()
{
    return m_plane->isDead();
}