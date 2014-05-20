//
//  Direct3DAssets.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#pragma once

#include <memory>

class GameSound;

class Direct3DAssets
{
public:
	std::unique_ptr<GameSound> m_ascendSound;
	std::unique_ptr<GameSound> m_scoreSound;
	std::unique_ptr<GameSound> m_hitSound;
	std::unique_ptr<GameSound> m_landSound;

	static Direct3DAssets * getInstance();

	Direct3DAssets();
};