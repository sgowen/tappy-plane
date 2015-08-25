//
//  Entity.cpp
//  nosfuratu
//
//  Created by Stephen Gowen on 8/3/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "Entity.h"

Entity::Entity() : m_fStateTime(0.0f), m_ID(getUniqueEntityID())
{
    // Empty
}

void Entity::update(float deltaTime)
{
    m_fStateTime += deltaTime;
}

int Entity::getID()
{
    return m_ID;
}

float Entity::getStateTime()
{
    return m_fStateTime;
}

int Entity::getUniqueEntityID()
{
    static int entityID = 0;
    
    return entityID++;
}
