//
//  Direct3DGameScreen.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#pragma once

#include "GameScreen.h"
#include "MediaEnginePlayer.h"
#include <memory>

class GameSound;

class Direct3DGameScreen : public GameScreen
{
public:
	Direct3DGameScreen(int levelIndex, int difficulty);

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
	std::unique_ptr<MediaEnginePlayer> m_mediaPlayer;
	std::unique_ptr<GameSound> m_acidDropSound;
	std::unique_ptr<GameSound> m_beginWaveSound;
	std::unique_ptr<GameSound> m_creepDeathSound;
	std::unique_ptr<GameSound> m_dragTowerSound;
	std::unique_ptr<GameSound> m_electricBoltSound;
	std::unique_ptr<GameSound> m_explosionSound;
	std::unique_ptr<GameSound> m_fireBoltSound;
	std::unique_ptr<GameSound> m_goalHitSound;
	std::unique_ptr<GameSound> m_iceBlastSound;
	std::unique_ptr<GameSound> m_lazerBeamSound;
	std::unique_ptr<GameSound> m_missileLaunchSound;
	std::unique_ptr<GameSound> m_placeTowerSound;
	std::unique_ptr<GameSound> m_plasmaBangSound;
	std::unique_ptr<GameSound> m_sellTowerSound;
	std::unique_ptr<GameSound> m_towerUpgradedSound;
	std::unique_ptr<GameSound> m_toxicCloudSound;

	float m_fGameScreenToDeviceScreenWidthRatio;
	float m_fGameScreenToDeviceScreenHeightRatio;
	float m_fDipToPixelRatio;
};