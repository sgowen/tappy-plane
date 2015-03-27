//
//  DirectXManager.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/17/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__DirectXManager__
#define __gowengamedev__DirectXManager__

#define MAX_BATCH_SIZE 1024
#define VERTICES_PER_RECTANGLE 4
#define INDICES_PER_RECTANGLE 6

#define DXManager (DirectXManager::getInstance())

#include "Direct3DProgram.h"

#include <vector>

class DirectXManager
{
public:
	ID3D11Device *m_device; // the device interface
	ID3D11DeviceContext *m_deviceContext; // the device context interface
	ID3D11Texture2D *m_renderTarget; // the render target texture
	ID3D11RenderTargetView *m_renderTargetView; // the render target interface
	ID3D11BlendState *m_blendState; // the blend state interface
	ID3D11Buffer *m_constantbuffer; // the constant buffer interface
	ID3D11Buffer *m_indexbuffer; // the index buffer interface

	// Used in SpriteBatcher
	ID3D11SamplerState *m_sbSamplerState; // the sampler state interfaces
	ID3D11VertexShader *m_sbVertexShader; // the vertex shader interface
	ID3D11PixelShader *m_sbPixelShader; // the pixel shader interface
	ID3D11InputLayout *m_sbInputLayout; // the input layout interface
	ID3D11Buffer *m_sbVertexBuffer; // the vertex buffer interface
	std::vector<TEXTURE_VERTEX> m_textureVertices;

	// Used in RectangleBatcher, LineBatcher, and CircleBatcher (Geometry)
	ID3D11VertexShader *m_gbVertexShader; // the vertex shader interface
	ID3D11PixelShader *m_gbPixelShader; // the pixel shader interface
	ID3D11InputLayout *m_gbInputLayout; // the input layout interface
	ID3D11Buffer *m_gbVertexBuffer; // the vertex buffer interface
	std::vector<COLOR_VERTEX> m_colorVertices;

	// All rendering takes place inside the same matrix
	DirectX::XMMATRIX m_matFinal;

	static DirectXManager * getInstance();

	void init(float width, float height);

	void initWindowSizeDependentResources(float width, float height);

	// Called by Batchers
	void prepareForSpriteRendering();
	void prepareForGeometryRendering();

	void cleanUp();

private:
	D3D_FEATURE_LEVEL m_featureLevel;

	void initDeviceResources();
	void createBlendState();
	void createSamplerState();
	void createInputLayoutForSpriteBatcher();
	void createInputLayoutForGeometryBatcher();
	void createVertexBufferForSpriteBatcher();
	void createVertexBufferForGeometryBatcher();
	void createIndexBuffer();
	void createConstantBuffer();
	void createMatrix();

	std::vector<short> createIndexValues();

	DirectXManager();
};

#endif /* defined(__gowengamedev__DirectXManager__) */