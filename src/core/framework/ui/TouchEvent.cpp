//
//  TouchEvent.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "TouchEvent.h"

TouchEvent::TouchEvent(float x, float y, Touch_Type type)
{
    m_type = type;
    m_fX = x;
    m_fY = y;
}

Touch_Type TouchEvent::getTouchType()
{
	return m_type;
}

void TouchEvent::setTouchType(Touch_Type touchType)
{
	m_type = touchType;
}

float TouchEvent::getX()
{
	return m_fX;
}

void TouchEvent::setX(float x)
{
	m_fX = x;
}

float TouchEvent::getY()
{
	return m_fY;
}

void TouchEvent::setY(float y)
{
	m_fY = y;
}