//
//  Assets.cpp
//  TappyPlane
//
//  Created by Stephen Gowen on 9/20/13.
//  Copyright (c) 2013 Techne Games. All rights reserved.
//

#include "pch.h"
#include "Direct3DAssets.h"
#include "Assets.h"
#include "GameSound.h"

Direct3DAssets * Direct3DAssets::getInstance()
{
	static Direct3DAssets *direct3DAssets = new Direct3DAssets();
	return direct3DAssets;
}

Direct3DAssets::Direct3DAssets()
{
	m_ascendSound = std::unique_ptr<GameSound>(new GameSound("assets\\ascend.wav"));
	m_scoreSound = std::unique_ptr<GameSound>(new GameSound("assets\\score.wav"));
	m_hitSound = std::unique_ptr<GameSound>(new GameSound("assets\\hit.wav"));
	m_landSound = std::unique_ptr<GameSound>(new GameSound("assets\\land.wav"));
}