//
//  Direct3DGameScreen.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 1/31/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "Direct3DGameScreen.h"
#include "RECTUtils.h"
#include "TouchEvent.h"
#include "GameObject.h"
#include "PlaneDynamicGameObject.h"
#include "Rectangle.h"
#include "Global.h"
#include "Direct3DAssets.h"
#include "GameSound.h"
#include "Assets.h"
#include "GameButton.h"

Direct3DGameScreen::Direct3DGameScreen(int deviceScreenWidth, int deviceScreenHeight) : GameScreen()
{
	m_renderer = std::unique_ptr<Direct3DRenderer>(new Direct3DRenderer());
	m_iDeviceScreenWidth = deviceScreenWidth;
	m_iDeviceScreenHeight = deviceScreenHeight;
	m_fGameScreenToDeviceScreenWidthRatio = deviceScreenWidth / SCREEN_WIDTH;
	m_fGameScreenToDeviceScreenHeightRatio = deviceScreenHeight / SCREEN_HEIGHT;
	m_fDipToPixelRatio = deviceScreenWidth == 768 ? 1.6f : deviceScreenWidth == 720 ? 1.5f : 1.0f;
}

void Direct3DGameScreen::platformInit()
{

}

void Direct3DGameScreen::load(Microsoft::WRL::ComPtr<ID3D11Device1> &d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext1> &d3dContext)
{
	m_renderer->load(d3dDevice, d3dContext, m_iDeviceScreenWidth, m_iDeviceScreenHeight);

	RECTUtils::getInstance()->setGameScreenToDeviceScreenRatio(m_fGameScreenToDeviceScreenWidthRatio, m_fGameScreenToDeviceScreenHeightRatio);
}

void Direct3DGameScreen::platformResume()
{
	Global::getSoundPlayerInstance()->Resume();
}

void Direct3DGameScreen::platformPause()
{
	Global::getSoundPlayerInstance()->Suspend();
}

void Direct3DGameScreen::present(Microsoft::WRL::ComPtr<ID3D11DeviceContext1> &d3dContext, Microsoft::WRL::ComPtr<ID3D11RenderTargetView> &renderTargetView, Microsoft::WRL::ComPtr<ID3D11DepthStencilView> &depthStencilView)
{
	float color[] = { m_fColor, m_fColor, m_fColor, 1.0f };

	d3dContext->ClearRenderTargetView(renderTargetView.Get(), color);
	d3dContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	d3dContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());

	m_renderer->renderWorldBackground(*m_world);

	m_renderer->renderWorldForeground(*m_world, *m_glove, m_fTitleAlpha);

	if (m_world->isGameOver())
	{
		m_renderer->renderWorldGameOver(*m_world, *m_okButton, *m_leaderboardsButton, m_iBestScore);
	}
}

void Direct3DGameScreen::touchToWorld(TouchEvent &touchEvent)
{
	m_touchPoint->set(touchEvent.getX() * m_fDipToPixelRatio / m_fGameScreenToDeviceScreenWidthRatio, SCREEN_HEIGHT - (touchEvent.getY() * m_fDipToPixelRatio / m_fGameScreenToDeviceScreenHeightRatio));
}

void Direct3DGameScreen::unload()
{
	if(m_gameState == RUNNING)
	{
		onPause();
	}

	m_renderer->cleanUp();
}

void Direct3DGameScreen::handleSoundId()
{
	short sound = Assets::getInstance()->getCurrentSoundId();
	Assets::getInstance()->resetCurrentSoundId();

	switch (sound)
	{
	case ASCEND_SOUND:
		Direct3DAssets::getInstance()->m_ascendSound->play();
		break;
	case SCORE_SOUND:
		Direct3DAssets::getInstance()->m_scoreSound->play();
		break;
	case HIT_SOUND:
		Direct3DAssets::getInstance()->m_hitSound->play();
		break;
	case LAND_SOUND:
		Direct3DAssets::getInstance()->m_landSound->play();
		break;
	default:
		break;
	}
}

bool Direct3DGameScreen::handleOnBackPressed()
{
	return false;
}