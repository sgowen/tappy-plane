#include "pch.h"
#include "Global.h"

XAudio2SoundPlayer * Global::getSoundPlayerInstance()
{
	static XAudio2SoundPlayer *player = new XAudio2SoundPlayer(48000);
	return player;
}