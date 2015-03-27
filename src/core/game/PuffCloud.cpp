//
//  PuffCloud.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "PuffCloud.h"
#include "Vector2D.h"
#include "Rectangle.h"

PuffCloud::PuffCloud(float x, float y, float width, float height, float angle) : GameObject(x, y, width, height, angle)
{
    m_fAlpha = 1;
}

void PuffCloud::update(float deltaTime)
{
    m_fAlpha -= deltaTime * 1.6f;
}

void PuffCloud::shift(float shiftX)
{
    m_position->sub(shiftX, 0);
}

float PuffCloud::getAlpha()
{
    return m_fAlpha;
}