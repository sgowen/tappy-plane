//
//  GameSound.h
//  TappyPlaneComp
//
//  Created by Stephen Gowen on 11/27/13.
//  Copyright (c) 2013 Techne Games. All rights reserved.
//

#pragma once

class GameSound
{
public:
	GameSound(Platform::String^ fileName);

	void play();

	void clearFrame();

private:
	int m_sounds[4];
	int m_iSoundIndex;

	int loadSound(Platform::String^ fileName);
};