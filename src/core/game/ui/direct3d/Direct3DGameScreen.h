//
//  Direct3DGameScreen.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#pragma once

#include "GameScreen.h"
#include <memory>

class GameSound;

class Direct3DGameScreen : public GameScreen
{
public:
	Direct3DGameScreen();

	void load(float deviceScreenWidth, float deviceScreenHeight, int deviceScreenDpWidth, int deviceScreenDpHeight);

	void updateForRenderResolutionChange(float width, float height);

	void handleSound();

	void handleMusic();

	void unload();

	ID3D11Texture2D* getTexture();

	virtual void touchToWorld(TouchEvent &touchEvent);

	virtual void platformResume();

	virtual void platformPause();

	virtual bool handleOnBackPressed();

private:
	std::unique_ptr<GameSound> m_ascendSound;
	std::unique_ptr<GameSound> m_scoreSound;
	std::unique_ptr<GameSound> m_hitSound;
	std::unique_ptr<GameSound> m_landSound;

	float m_fGameScreenToDeviceScreenWidthRatio;
	float m_fGameScreenToDeviceScreenHeightRatio;
	float m_fDipToPixelRatio;
};