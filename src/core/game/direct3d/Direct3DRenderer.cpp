//
//  Direct3DRenderer.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "pch.h"
#include "macros.h"
#include "Direct3DRenderer.h"
#include "GameObject.h"
#include "TextureRegion.h"
#include "Assets.h"
#include "Vector2D.h"
#include "Font.h"
#include "TextureWrapper.h"
#include "Line.h"
#include "Rectangle.h"
#include "BasicReaderWriter.h"
#include "DDSTextureLoader.h"
#include "SpriteBatcher.h"
#include "Direct3DRectangleBatcher.h"
#include "Direct3DSpriteBatcher.h"
#include "Direct3DLineBatcher.h"
#include "Direct3DCircleBatcher.h"
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
#include "DirectXManager.h"

#include <string>
#include <sstream>

using namespace DirectX;

ID3D11ShaderResourceView *m_backgroundShaderResourceView;
ID3D11ShaderResourceView *m_creepsShaderResourceView;
ID3D11ShaderResourceView *m_spawnPlatformsProjectilesTowersShaderResourceView;
ID3D11ShaderResourceView *m_looseObjectsExplosionsShaderResourceView;
ID3D11ShaderResourceView *m_topLevelUiShaderResourceView;

Direct3DRenderer::Direct3DRenderer() : Renderer()
{
	m_spriteBatcher = std::unique_ptr<Direct3DSpriteBatcher>(new Direct3DSpriteBatcher());
	m_rectangleBatcher = std::unique_ptr<Direct3DRectangleBatcher>(new Direct3DRectangleBatcher(false));
	m_lineBatcher = std::unique_ptr<Direct3DLineBatcher>(new Direct3DLineBatcher());
	m_circleBatcher = std::unique_ptr<Direct3DCircleBatcher>(new Direct3DCircleBatcher());

	CreateDDSTextureFromFile(DXManager->m_device, L"Assets\\background_texture.dds", NULL, &m_backgroundShaderResourceView, NULL);
	CreateDDSTextureFromFile(DXManager->m_device, L"Assets\\creeps.dds", NULL, &m_creepsShaderResourceView, NULL);
	CreateDDSTextureFromFile(DXManager->m_device, L"Assets\\spawn_platforms_projectiles_towers.dds", NULL, &m_spawnPlatformsProjectilesTowersShaderResourceView, NULL);
	CreateDDSTextureFromFile(DXManager->m_device, L"Assets\\loose_objects_explosions.dds", NULL, &m_looseObjectsExplosionsShaderResourceView, NULL);
	CreateDDSTextureFromFile(DXManager->m_device, L"Assets\\top_level_ui.dds", NULL, &m_topLevelUiShaderResourceView, NULL);

	m_backgroundTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(m_backgroundShaderResourceView));
	m_creepsTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(m_creepsShaderResourceView));
	m_spawnPlatformsProjectilesTowersTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(m_spawnPlatformsProjectilesTowersShaderResourceView));
	m_looseObjectsTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(m_looseObjectsExplosionsShaderResourceView));
	m_topLevelUiTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(m_topLevelUiShaderResourceView));
}

void Direct3DRenderer::clearScreenWithColor(float r, float g, float b, float a)
{
	float color[] = { r, g, b, a };

	// set our new render target object as the active render target
	DXManager->m_deviceContext->OMSetRenderTargets(1, &DXManager->m_renderTargetView, nullptr);

	DXManager->m_deviceContext->ClearRenderTargetView(DXManager->m_renderTargetView, color);
}

void Direct3DRenderer::beginFrame()
{
	// Not Needed Yet
}

void Direct3DRenderer::endFrame()
{
	// Not Needed Yet
}

void Direct3DRenderer::cleanUp()
{
	m_backgroundShaderResourceView->Release();
	m_creepsShaderResourceView->Release();
	m_spawnPlatformsProjectilesTowersShaderResourceView->Release();
	m_looseObjectsExplosionsShaderResourceView->Release();
	m_topLevelUiShaderResourceView->Release();
}