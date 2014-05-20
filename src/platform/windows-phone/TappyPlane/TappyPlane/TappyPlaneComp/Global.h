#pragma once

#include "Helpers\XAudio2SoundPlayer.h"

class Global
{
public:
	static XAudio2SoundPlayer * getSoundPlayerInstance();
};