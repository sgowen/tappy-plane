//
//  Direct3DRenderer.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "DirectXHelper.h"
#include "Direct3DRenderer.h"
#include "Direct3DAssets.h"
#include "Assets.h"
#include "RECTUtils.h"
#include "PlaneDynamicGameObject.h"
#include "World.h"
#include "TextureRegion.h"
#include <Effects.h>
#include "Obstacle.h"
#include "Font.h"
#include "GameButton.h"
#include "Glove.h"
#include "PuffCloud.h"
#include <string>

using namespace DirectX;

Direct3DRenderer::Direct3DRenderer() : Renderer()
{

}

void Direct3DRenderer::load(Microsoft::WRL::ComPtr<ID3D11Device1> &d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext1> &d3dContext, int deviceScreenWidth, int deviceScreenHeight)
{
	// Create the SpriteBatch
	m_spriteBatch = std::unique_ptr<SpriteBatch>(new SpriteBatch(d3dContext.Get()));

	// Initialize Textures
	DX::ThrowIfFailed(CreateDDSTextureFromFile(d3dDevice.Get(), L"Assets\\game.dds", NULL, &m_gameShaderResourceView, NULL));
	DX::ThrowIfFailed(CreateDDSTextureFromFile(d3dDevice.Get(), L"Assets\\background.dds", NULL, &m_backgroundShaderResourceView, NULL));

	// Clear the blend state description.
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	// To create an alpha enabled blend state description change BlendEnable to TRUE and DestBlend to D3D11_BLEND_INV_SRC_ALPHA.
	// The other settings are set to their default values which can be looked up in the Windows DirectX Graphics Documentation.
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // Instead of D3D11_BLEND_ONE
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // Instead of D3D11_BLEND_ZERO
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE; // Instead of D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; //Instead of D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	//We then create an alpha enabled blending state using the description we just setup.
	// Create the blend state using the description.
	HRESULT result = d3dDevice.Get()->CreateBlendState(&blendDesc, &m_alphaEnableBlendingState);
	if (FAILED(result))
	{
		// Panic!
	}

	// Set up Stuff for PrimitiveBatch

	m_primitiveBatch = std::unique_ptr<PrimitiveBatch<VertexPositionColor>>(new PrimitiveBatch<VertexPositionColor>(d3dContext.Get()));

	m_basicEffect = std::unique_ptr<BasicEffect>(new BasicEffect(d3dDevice.Get()));

	m_basicEffect->SetProjection(XMMatrixOrthographicOffCenterRH(0, deviceScreenWidth, deviceScreenHeight, 0, 0, 1));
	m_basicEffect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;

	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	d3dDevice.Get()->CreateInputLayout(VertexPositionColor::InputElements, VertexPositionColor::InputElementCount, shaderByteCode, byteCodeLength, &m_inputLayout);
}

void Direct3DRenderer::renderWorldBackground(World &world)
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_backgroundShaderResourceView, RECTUtils::getInstance()->getRECTForCoordinates(WORLD_BACKGROUND_X, WORLD_BACKGROUND_Y, WORLD_BACKGROUND_WIDTH + 1, WORLD_BACKGROUND_HEIGHT, false), &Assets::getWorldBackgroundTextureRegion().getSourceRECT(), Colors::White, 0, XMFLOAT2(0, 0), SpriteEffects_None, 0);
	m_spriteBatch->End();
}

void Direct3DRenderer::renderWorldForeground(World &world, Glove &glove, float titleAlpha)
{
	m_spriteBatch->Begin();
	for (std::vector<std::unique_ptr<Obstacle>>::iterator itr = world.getObstacles().begin(); itr != world.getObstacles().end(); ++itr)
	{
		renderObstacle((**itr));
	}
	m_spriteBatch->End();

	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_gameShaderResourceView, RECTUtils::getInstance()->getRECTForGameObject(world.getPlane(), true), &Assets::getPlaneTextureRegion(world.getPlane()).getSourceRECT(), Colors::White, DEGREES_TO_RADIANS_WP(world.getPlane().getAngle()), XMFLOAT2(PLANE_TEXTURE_REGION_WIDTH / 2, PLANE_TEXTURE_REGION_HEIGHT / 2), SpriteEffects_None, 0);
	m_spriteBatch->End();

	if (world.getPlane().getPuffClouds().size() > 0)
	{
		m_spriteBatch->Begin(SpriteSortMode::SpriteSortMode_Deferred, m_alphaEnableBlendingState);

		for (std::vector<std::unique_ptr<PuffCloud>>::iterator itr = world.getPlane().getPuffClouds().begin(); itr != world.getPlane().getPuffClouds().end(); itr++)
		{
			DirectX::XMVECTORF32 puffCloudColor = { 1, 1, 1, (*itr)->getAlpha() };
			m_spriteBatch->Draw(m_gameShaderResourceView, RECTUtils::getInstance()->getRECTForGameObject((**itr), true), &Assets::getPuffLargeTextureRegion().getSourceRECT(), puffCloudColor, DEGREES_TO_RADIANS_WP((*itr)->getAngle()), XMFLOAT2(PUFF_LARGE_TEXTURE_REGION_WIDTH / 2, PUFF_LARGE_TEXTURE_REGION_HEIGHT / 2), SpriteEffects_None, 0);
		}

		m_spriteBatch->End();
	}

	// Bottom Bar (foreground)
	m_spriteBatch->Begin();
	renderGameObject(world.getForegroundLeft(), Assets::getWorldForegroundLeftTextureRegion(world.getEnvironmentType()));
	renderGameObject(world.getForegroundRight(), Assets::getWorldForegroundRightTextureRegion(world.getEnvironmentType()));
	m_spriteBatch->End();

	if (titleAlpha > 0)
	{
		DirectX::XMVECTORF32 titleColor = { 1, 1, 1, titleAlpha };

		m_spriteBatch->Begin(SpriteSortMode::SpriteSortMode_Deferred, m_alphaEnableBlendingState);
		m_spriteBatch->Draw(m_backgroundShaderResourceView, RECTUtils::getInstance()->getRECTForCoordinates(TITLE_X, TITLE_Y, TITLE_WIDTH, TITLE_HEIGHT, false), &Assets::getTitleTextureRegion().getSourceRECT(), titleColor, 0, XMFLOAT2(0, 0), SpriteEffects_None, 0);
		m_spriteBatch->Draw(m_backgroundShaderResourceView, RECTUtils::getInstance()->getRECTForCoordinates(glove.getPosition().getX(), glove.getPosition().getY(), glove.getWidth(), glove.getHeight(), false), &Assets::getGloveTextureRegion(glove).getSourceRECT(), titleColor, 0, XMFLOAT2(0, 0), SpriteEffects_None, 0);
		m_spriteBatch->Draw(m_backgroundShaderResourceView, RECTUtils::getInstance()->getRECTForCoordinates(glove.getPosition().getX() - 3.5f, glove.getPosition().getY(), 4, 2, false), &Assets::getTapLeftTextureRegion().getSourceRECT(), titleColor, 0, XMFLOAT2(0, 0), SpriteEffects_None, 0);
		m_spriteBatch->Draw(m_backgroundShaderResourceView, RECTUtils::getInstance()->getRECTForCoordinates(glove.getPosition().getX() + 3.5f, glove.getPosition().getY(), 4, 2, false), &Assets::getTapRightTextureRegion().getSourceRECT(), titleColor, 0, XMFLOAT2(0, 0), SpriteEffects_None, 0);
		m_spriteBatch->End();
	}

	if (!world.isGameOver() && world.getScore() > 0 && titleAlpha < 0)
	{
		std::string score = std::to_string(world.getScore());
		static DirectX::XMVECTORF32 scoreColor = { 1, 1, 1, 1 };

		m_spriteBatch->Begin(SpriteSortMode::SpriteSortMode_Deferred, m_alphaEnableBlendingState);
		m_font->renderText(*m_spriteBatch, m_gameShaderResourceView, score, SCORE_FONT_X, SCORE_FONT_Y, SCORE_FONT_WIDTH, SCORE_FONT_HEIGHT, scoreColor, true);
		m_spriteBatch->End();
	}
}

void Direct3DRenderer::renderWorldGameOver(World &world, GameButton &okButton, GameButton &leaderboardsButton, int bestScore)
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_gameShaderResourceView, RECTUtils::getInstance()->getRECTForCoordinates(GAME_OVER_X, GAME_OVER_Y, GAME_OVER_WIDTH, GAME_OVER_HEIGHT, false), &Assets::getGameOverTextureRegion().getSourceRECT(), Colors::White, 0, XMFLOAT2(0, 0), SpriteEffects_None, 0);
	m_spriteBatch->Draw(m_gameShaderResourceView, RECTUtils::getInstance()->getRECTForCoordinates(DIALOG_GAME_OVER_X, DIALOG_GAME_OVER_Y, DIALOG_GAME_OVER_WIDTH, DIALOG_GAME_OVER_HEIGHT, false), &Assets::getDialogTextureRegion().getSourceRECT(), Colors::White, 0, XMFLOAT2(0, 0), SpriteEffects_None, 0);
	renderGameObject(okButton, Assets::getOkButtonTextureRegion());
	renderGameObject(leaderboardsButton, Assets::getLeaderboardsButtonTextureRegion());

	if (world.getScore() >= 50)
	{
		m_spriteBatch->Draw(m_gameShaderResourceView, RECTUtils::getInstance()->getRECTForCoordinates(MEDAL_X, MEDAL_Y, MEDAL_WIDTH, MEDAL_HEIGHT, false), &Assets::getGoldMedalTextureRegion().getSourceRECT(), Colors::White, 0, XMFLOAT2(0, 0), SpriteEffects_None, 0);
	}
	else if (world.getScore() >= 25)
	{
		m_spriteBatch->Draw(m_gameShaderResourceView, RECTUtils::getInstance()->getRECTForCoordinates(MEDAL_X, MEDAL_Y, MEDAL_WIDTH, MEDAL_HEIGHT, false), &Assets::getSilverMedalTextureRegion().getSourceRECT(), Colors::White, 0, XMFLOAT2(0, 0), SpriteEffects_None, 0);
	}
	else if (world.getScore() >= 10)
	{
		m_spriteBatch->Draw(m_gameShaderResourceView, RECTUtils::getInstance()->getRECTForCoordinates(MEDAL_X, MEDAL_Y, MEDAL_WIDTH, MEDAL_HEIGHT, false), &Assets::getBronzeMedalTextureRegion().getSourceRECT(), Colors::White, 0, XMFLOAT2(0, 0), SpriteEffects_None, 0);
	}

	m_spriteBatch->End();

	std::string scoreString = std::to_string(world.getScore());
	std::string bestScoreString = std::to_string(bestScore);

	static DirectX::XMVECTORF32 scoreColor = { 1, 1, 1, 1 };

	m_spriteBatch->Begin();
	m_font->renderText(*m_spriteBatch, m_gameShaderResourceView, scoreString, SCORE_FONT_IN_WINDOW_X, SCORE_FONT_IN_WINDOW_Y, FONT_IN_WINDOW_WIDTH, FONT_IN_WINDOW_HEIGHT, scoreColor, false, true);
	m_font->renderText(*m_spriteBatch, m_gameShaderResourceView, bestScoreString, BEST_FONT_IN_WINDOW_X, BEST_FONT_IN_WINDOW_Y, FONT_IN_WINDOW_WIDTH, FONT_IN_WINDOW_HEIGHT, scoreColor, false, true);
	m_spriteBatch->End();
}

void Direct3DRenderer::cleanUp()
{
	m_gameShaderResourceView->Release();
	m_backgroundShaderResourceView->Release();
}

void Direct3DRenderer::renderObstacle(Obstacle &obstacle)
{
	for (std::vector<std::unique_ptr<SpikeGameObject>>::iterator itr = obstacle.getSpikes().begin(); itr != obstacle.getSpikes().end(); ++itr)
	{
		m_spriteBatch->Draw(m_gameShaderResourceView, RECTUtils::getInstance()->getRECTForGameObject((**itr), true), &Assets::getWorldSpikeTextureRegion((**itr).getType()).getSourceRECT(), Colors::White, DEGREES_TO_RADIANS_WP((*itr)->getAngle()), XMFLOAT2(SPIKE_TEXTURE_REGION_WIDTH / 2, SPIKE_TEXTURE_REGION_HEIGHT / 2), SpriteEffects_None, 0);
	}
}

void Direct3DRenderer::renderGameObject(GameObject &go, TextureRegion tr)
{
	m_spriteBatch->Draw(m_gameShaderResourceView, RECTUtils::getInstance()->getRECTForGameObject(go, false), &tr.getSourceRECT(), Colors::White, 0, XMFLOAT2(0, 0), SpriteEffects_None, 0);
}