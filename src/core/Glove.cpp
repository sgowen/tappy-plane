//
//  Glove.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "Glove.h"
#include "Vector2D.h"
#include "Rectangle.h"

Glove::Glove(float x, float y, float width, float height) : GameObject(x, y, width, height, 0)
{
	m_fStateTime = 0;
}

void Glove::update(float deltaTime)
{
    m_fStateTime += deltaTime;
}

float Glove::getStateTime()
{
    return m_fStateTime;
}