//
//  Direct3DGameScreen.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "pch.h"
#include "Direct3DGameScreen.h"
#include "Vector2D.h"
#include "TouchEvent.h"
#include "Vector2D.h"
#include "Rectangle.h"
#include "Assets.h"
#include "OverlapTester.h"
#include "GameListener.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Font.h"
#include "Direct3DRenderer.h"
#include "Global.h"
#include "GameSound.h"
#include "SpriteBatcher.h"
#include "LineBatcher.h"
#include "RectangleBatcher.h"
#include "CircleBatcher.h"
#include "GameListener.h"
#include "BackgroundElements.h"
#include "TimeButton.h"
#include "Dialog.h"
#include "TouchCursor.h"
#include "Text.h"
#include "Asteroid.h"
#include "ShipModule.h"
#include "CoreShipModule.h"
#include "TowerCursor.h"
#include "Rectangle.h"
#include "TowerOptionButton.h"
#include "Circle.h"
#include "GameConstants.h"
#include "ResourceConstants.h"
#include "DirectXManager.h"

Direct3DGameScreen::Direct3DGameScreen(int levelIndex, int difficulty) : GameScreen(levelIndex, difficulty)
{
	// No further setup
}

void Direct3DGameScreen::load(float deviceScreenWidth, float deviceScreenHeight, int deviceScreenDpWidth, int deviceScreenDpHeight)
{
	m_iDeviceScreenWidth = deviceScreenWidth;
	m_iDeviceScreenHeight = deviceScreenHeight;
	m_fGameScreenToDeviceScreenWidthRatio = deviceScreenWidth / SCREEN_WIDTH;
	m_fGameScreenToDeviceScreenHeightRatio = deviceScreenHeight / SCREEN_HEIGHT;
	m_fDipToPixelRatio = (float)deviceScreenWidth / (float)deviceScreenDpWidth;

	DXManager->init(deviceScreenWidth, deviceScreenHeight);

	m_renderer = std::unique_ptr<Direct3DRenderer>(new Direct3DRenderer());

	// Load Background Music
	m_mediaPlayer = std::unique_ptr<MediaEnginePlayer>(new MediaEnginePlayer);
	m_mediaPlayer->Initialize(DXManager->m_device, DXGI_FORMAT_B8G8R8A8_UNORM);

	m_beginWaveSound = std::unique_ptr<GameSound>(new GameSound("assets\\begin_wave.wav"));
	m_dragTowerSound = std::unique_ptr<GameSound>(new GameSound("assets\\drag_tower.wav"));
	m_placeTowerSound = std::unique_ptr<GameSound>(new GameSound("assets\\place_tower.wav"));
	m_sellTowerSound = std::unique_ptr<GameSound>(new GameSound("assets\\sell_tower.wav"));
	m_towerUpgradedSound = std::unique_ptr<GameSound>(new GameSound("assets\\tower_upgraded.wav"));
	m_creepDeathSound = std::unique_ptr<GameSound>(new GameSound("assets\\creep_death.wav"));
	m_lazerBeamSound = std::unique_ptr<GameSound>(new GameSound("assets\\lazer_beam.wav"));
	m_missileLaunchSound = std::unique_ptr<GameSound>(new GameSound("assets\\missile_launch.wav"));
	m_explosionSound = std::unique_ptr<GameSound>(new GameSound("assets\\explosion.wav"));
	m_iceBlastSound = std::unique_ptr<GameSound>(new GameSound("assets\\ice_blast.wav"));
	m_electricBoltSound = std::unique_ptr<GameSound>(new GameSound("assets\\electric_bolt.wav"));
	m_plasmaBangSound = std::unique_ptr<GameSound>(new GameSound("assets\\plasma_bang.wav"));
	m_fireBoltSound = std::unique_ptr<GameSound>(new GameSound("assets\\fire_bolt.wav"));
	m_acidDropSound = std::unique_ptr<GameSound>(new GameSound("assets\\acid_drop.wav"));
	m_toxicCloudSound = std::unique_ptr<GameSound>(new GameSound("assets\\toxic_cloud.wav"));
	m_goalHitSound = std::unique_ptr<GameSound>(new GameSound("assets\\goal_hit.wav"));
}

void Direct3DGameScreen::updateForRenderResolutionChange(float width, float height)
{
	m_iDeviceScreenWidth = width;
	m_iDeviceScreenHeight = height;

	ID3D11RenderTargetView* nullViews[] = { nullptr };
	DXManager->m_deviceContext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
	DXManager->m_renderTarget = nullptr;
	DXManager->m_renderTargetView = nullptr;
	DXManager->m_deviceContext->Flush();

	DXManager->initWindowSizeDependentResources(width, height);
}

void Direct3DGameScreen::handleSound()
{
	short soundId;
	while ((soundId = Assets::getInstance()->getFirstSoundId()) > 0)
	{
		Assets::getInstance()->eraseFirstSoundId();

		switch (soundId)
		{
		case SOUND_ACID_DROP:
			m_acidDropSound->play();
			break;
		case SOUND_BEGIN_WAVE:
			m_beginWaveSound->play();
			break;
		case SOUND_CREEP_DEATH:
			m_creepDeathSound->play();
			break;
		case SOUND_DRAG_TOWER:
			m_dragTowerSound->play();
			break;
		case SOUND_ELECTRIC_BOLT:
			m_electricBoltSound->play();
			break;
		case SOUND_EXPLOSION:
			m_explosionSound->play();
			break;
		case SOUND_FIRE_BOLT:
			m_fireBoltSound->play();
			break;
		case SOUND_GOAL_HIT:
			m_goalHitSound->play();
			break;
		case SOUND_ICE_BLAST:
			m_iceBlastSound->play();
			break;
		case SOUND_LAZER_BEAM:
			m_lazerBeamSound->play();
			break;
		case SOUND_MISSILE_LAUNCH:
			m_missileLaunchSound->play();
			break;
		case SOUND_PLACE_TOWER:
			m_placeTowerSound->play();
			break;
		case SOUND_PLASMA_BANG:
			m_plasmaBangSound->play();
			break;
		case SOUND_SELL_TOWER:
			m_sellTowerSound->play();
			break;
		case SOUND_TOWER_UPGRADED:
			m_towerUpgradedSound->play();
			break;
		case SOUND_TOXIC_CLOUD:
			m_toxicCloudSound->play();
			break;
		default:
			continue;
		}
	}
}

void Direct3DGameScreen::handleMusic()
{
	short musicId = Assets::getInstance()->getMusicId();
	Assets::getInstance()->setMusicId(0);

	switch (musicId)
	{
	case MUSIC_STOP:
		m_mediaPlayer->Pause();
		break;
	case MUSIC_PLAY_MAP_SPACE:
		m_mediaPlayer->SetSource("assets\\bgm.wav");
		m_mediaPlayer->Play();
		break;
	default:
		break;
	}
}

void Direct3DGameScreen::unload()
{
	if (m_gameState == RUNNING)
	{
		onPause();
	}

	m_mediaPlayer->Shutdown();

	m_renderer->cleanUp();

	DXManager->cleanUp();
}

ID3D11Texture2D* Direct3DGameScreen::getTexture()
{
	return DXManager->m_renderTarget;
}

void Direct3DGameScreen::touchToWorld(TouchEvent &touchEvent)
{
	m_touchPoint->set(touchEvent.getX() * m_fDipToPixelRatio / m_fGameScreenToDeviceScreenWidthRatio, SCREEN_HEIGHT - (touchEvent.getY() * m_fDipToPixelRatio / m_fGameScreenToDeviceScreenHeightRatio));
}

void Direct3DGameScreen::platformResume()
{
	Global::getSoundPlayerInstance()->Resume();
}

void Direct3DGameScreen::platformPause()
{
	Global::getSoundPlayerInstance()->Suspend();
}

bool Direct3DGameScreen::handleOnBackPressed()
{
	if (m_gameState == RUNNING)
	{
		onPause();

		return true;
	}

	return false;
}