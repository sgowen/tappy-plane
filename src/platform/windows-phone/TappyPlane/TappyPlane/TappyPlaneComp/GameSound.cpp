//
//  GameSound.cpp
//  TappyPlaneComp
//
//  Created by Stephen Gowen on 11/27/13.
//  Copyright (c) 2013 Techne Games. All rights reserved.
//

#include "pch.h"
#include "GameSound.h"
#include "Global.h"
#include "Helpers/SoundFileReader.h"

GameSound::GameSound(Platform::String^ fileName)
{
	m_sounds[0] = loadSound(fileName);
	m_sounds[1] = loadSound(fileName);
	m_sounds[2] = loadSound(fileName);
	m_sounds[3] = loadSound(fileName);

	m_iSoundIndex = 0;
}

void GameSound::play()
{
	Global::getSoundPlayerInstance()->PlaySound(m_sounds[m_iSoundIndex++]);

		if(m_iSoundIndex > 3)
		{
			m_iSoundIndex = 0;
		}
}

int GameSound::loadSound(Platform::String^ fileName)
{
	SoundFileReader sound(fileName);
	return Global::getSoundPlayerInstance()->AddSound(sound.GetSoundFormat(), sound.GetSoundData());
}