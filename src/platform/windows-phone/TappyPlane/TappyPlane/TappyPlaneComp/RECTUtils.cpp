//
//  RECTUtils.cpp
//  game-framework
//
//  Created by Stephen Gowen on 10/6/13.
//  Copyright (c) 2013 Techne Games. All rights reserved.
//

#include "pch.h"
#include "RECTUtils.h"
#include "Vector2D.h"

void RECTUtils::setGameScreenToDeviceScreenRatio(float gameScreenToDeviceScreenWidthRatio, float gameScreenToDeviceScreenHeightRatio)
{
	m_fGameScreenToDeviceScreenWidthRatio = gameScreenToDeviceScreenWidthRatio;
	m_fGameScreenToDeviceScreenHeightRatio = gameScreenToDeviceScreenHeightRatio;
}

RECT RECTUtils::getRECTForGameObject(GameObject &gameObject, bool hasRotation)
{
	return getRECTForCoordinates(gameObject.getPosition().getX(), gameObject.getPosition().getY(), gameObject.getWidth(), gameObject.getHeight(), hasRotation);
}

RECT RECTUtils::getRECTForCoordinates(float x, float y, float w, float h, bool hasRotation)
{
	long left = (x - w / 2) * m_fGameScreenToDeviceScreenWidthRatio + 0.5f;
	long top = (SCREEN_HEIGHT - y - h / 2) * m_fGameScreenToDeviceScreenHeightRatio + 0.5f;
	long width = w * m_fGameScreenToDeviceScreenWidthRatio + 0.5f;
	long height = h * m_fGameScreenToDeviceScreenHeightRatio + 0.5f;
	
	long xModifier = hasRotation ? width / 2 : 0;
	long yModifier = hasRotation ? height / 2 : 0;
	RECT currentRECT =
	{
		left + xModifier,
		top + yModifier,
		left + width + xModifier,
		top + height + yModifier
	};
	
	return currentRECT;
}

float RECTUtils::convertGameXToScreenX(float x)
{
	return x * m_fGameScreenToDeviceScreenWidthRatio;
}

float RECTUtils::convertGameYToScreenY(float y)
{
	return (SCREEN_HEIGHT - y) * m_fGameScreenToDeviceScreenHeightRatio;
}