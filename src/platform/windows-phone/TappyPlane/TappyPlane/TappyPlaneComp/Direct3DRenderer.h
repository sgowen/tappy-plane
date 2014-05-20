//
//  Direct3DRenderer.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#pragma once

#include "Renderer.h"
#include <DDSTextureLoader.h>
#include <SpriteBatch.h>
#include <PrimitiveBatch.h>
#include "CommonStates.h"
#include "VertexTypes.h"
#include <Effects.h>

class GameObject;
class World;
class TextureRegion;
class Glove;

class Direct3DRenderer : public Renderer
{
public:
	Direct3DRenderer();
	
	void load(Microsoft::WRL::ComPtr<ID3D11Device1> &d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext1> &d3dContext, int deviceScreenWidth, int deviceScreenHeight);

	virtual void renderWorldBackground(World &world);

	virtual void renderWorldForeground(World &world, Glove &glove, float titleAlpha);

    virtual void renderWorldGameOver(World &world, GameButton &okButton, GameButton &leaderboardsButton, int bestScore);

	void cleanUp();

private:
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	ID3D11ShaderResourceView *m_gameShaderResourceView;
	ID3D11ShaderResourceView *m_backgroundShaderResourceView;
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	ID3D11BlendState *m_alphaEnableBlendingState;

	int m_iDeviceScreenWidth;
	int m_iDeviceScreenHeight;

	virtual void renderObstacle(Obstacle &obstacle);

	virtual void renderGameObject(GameObject &go, TextureRegion tr);
};