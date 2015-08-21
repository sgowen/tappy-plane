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
#include "Rectangle.h"
#include "Circle.h"
#include "DirectXManager.h"

#include <string>
#include <sstream>

using namespace DirectX;

ID3D11ShaderResourceView *m_backgroundShaderResourceView;
ID3D11ShaderResourceView *m_gameShaderResourceView;

Direct3DRenderer::Direct3DRenderer() : Renderer()
{
	m_spriteBatcher = std::unique_ptr<Direct3DSpriteBatcher>(new Direct3DSpriteBatcher());

	CreateDDSTextureFromFile(DXManager->m_device, L"Assets\\background.dds", NULL, &m_backgroundShaderResourceView, NULL);
	CreateDDSTextureFromFile(DXManager->m_device, L"Assets\\game.dds", NULL, &m_gameShaderResourceView, NULL);

	m_backgroundTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(m_backgroundShaderResourceView));
	m_gameTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(m_gameShaderResourceView));
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
	m_gameShaderResourceView->Release();
}