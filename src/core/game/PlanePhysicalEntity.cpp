//
//  PlanePhysicalEntity.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/10/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "macros.h"
#include "GameConstants.h"
#include "ResourceConstants.h"
#include "PlanePhysicalEntity.h"
#include "Vector2D.h"
#include "Rectangle.h"
#include "Assets.h"
#include "GameListener.h"
#include <random>

PlanePhysicalEntity::PlanePhysicalEntity(float x, float y, float width, float height) : PhysicalEntity(x, y, width, height, 0)
{
    m_velocity->set(0, 0);
    m_acceleration->set(0, -60);
	m_bounds->getLowerLeft().set(x - width / 4, y - height / 4);
    m_bounds->setWidth(width / 2);
	m_bounds->setHeight(height / 2);
    
    m_fTimeSinceFlap = 0;
    m_fAngle = 360;
    m_isFlying = false;
    m_isHit = false;
    m_isDead = false;
    
    int randomInt = rand() % 4;
    m_type = randomInt == 0 ? BLUE : randomInt == 1 ? GREEN : randomInt == 2 ? RED : YELLOW;
}

void PlanePhysicalEntity::startFlying()
{
    m_isFlying = true;
}

void PlanePhysicalEntity::update(float deltaTime, float shiftX)
{
    if (!m_isHit && !m_isDead)
    {
        m_fStateTime += deltaTime;
        
        for (std::vector<std::unique_ptr<PuffCloud>>::iterator itr = m_puffClouds.begin(); itr != m_puffClouds.end(); itr++)
        {
            (*itr)->shift(shiftX);
        }
    }
    
    if(m_isFlying)
    {
        m_fTimeSinceFlap += deltaTime;
        
        if(m_fTimeSinceFlap > 0.15f)
        {
            m_fAngle -= deltaTime * 160;
            
            if (m_fAngle < 270)
            {
                m_fAngle = 270;
            }
        }
        
        for (std::vector<std::unique_ptr<PuffCloud>>::iterator itr = m_puffClouds.begin(); itr != m_puffClouds.end(); )
        {
            (*itr)->update(deltaTime);
            
            if((*itr)->getAlpha() < 0)
            {
                itr = m_puffClouds.erase(itr);
            }
            else
            {
                itr++;
            }
        }
        
        if (!m_isDead)
        {
            m_velocity->add(m_acceleration->getX() * deltaTime, m_acceleration->getY() * deltaTime);
            m_position->add(m_velocity->getX() * deltaTime, m_velocity->getY() * deltaTime);
            m_bounds->getLowerLeft().set(getPosition().getX() - getWidth() / 4, getPosition().getY() - getHeight() / 4);
            m_bounds->setAngle(getAngle());
            
            if(m_position->getY() > GAME_HEIGHT - (getHeight() / 2))
            {
                m_position->set(m_position->getX(), GAME_HEIGHT - (getHeight() / 2));
            }
            else if(m_position->getY() < GAME_WORLD_BASE)
            {
                m_isDead = true;
                GameListener::getInstance()->playSound(LAND_SOUND);
            }
        }
    }
}

void PlanePhysicalEntity::ascend()
{
    if(!m_isHit && !m_isDead)
    {
        m_velocity->set(0, 24.0f);
        
        m_fTimeSinceFlap = 0;
        
        m_fAngle = 384;
        
        float radians = DEGREES_TO_RADIANS(m_fAngle);
        float cos = cosf(radians);
        float sin = sinf(radians);
        
        float height = getHeight() / 3 * 2;
        
        m_puffClouds.push_back(std::unique_ptr<PuffCloud>(new PuffCloud(getPosition().getX() - (cos * 2.4f), getPosition().getY() - (sin * 2.4f), height * 1.33f, height, m_fAngle)));
        
        GameListener::getInstance()->playSound(ASCEND_SOUND);
    }
}

void PlanePhysicalEntity::hit()
{
    m_isHit = true;
    m_velocity->set(0, 0);
    GameListener::getInstance()->playSound(HIT_SOUND);
}

std::vector<std::unique_ptr<PuffCloud>> & PlanePhysicalEntity::getPuffClouds()
{
    return m_puffClouds;
}

bool PlanePhysicalEntity::isFlying()
{
    return m_isFlying;
}

bool PlanePhysicalEntity::isHit()
{
    return m_isHit;
}

bool PlanePhysicalEntity::isDead()
{
    return m_isDead;
}

Plane_Type PlanePhysicalEntity::getType()
{
    return m_type;
}