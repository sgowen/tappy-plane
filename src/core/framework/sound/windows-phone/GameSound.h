//
//  GameSound.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2013 Gowen Game Dev. All rights reserved.
//

#pragma once

#include "XAudio2SoundPlayer.h"

class GameSound
{
public:
	static XAudio2SoundPlayer * getSoundPlayerInstance();

	GameSound(Platform::String^ fileName);

	void play();

	void clearFrame();

private:
	int m_sounds[4];
	int m_iSoundIndex;

	int loadSound(Platform::String^ fileName);
};