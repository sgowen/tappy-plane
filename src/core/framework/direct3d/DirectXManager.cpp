//
//  DirectXManager.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/17/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "pch.h"
#include "DirectXManager.h"
#include "GameConstants.h"
#include "BasicReaderWriter.h"
#include "DirectXHelper.h"

DirectXManager * DirectXManager::getInstance()
{
	static DirectXManager *directXManager = new DirectXManager();
	return directXManager;
}

void DirectXManager::init(float width, float height)
{
	initDeviceResources();
	initWindowSizeDependentResources(width, height);
	createBlendState();
	createSamplerState();
	createInputLayoutForSpriteBatcher();
	createInputLayoutForGeometryBatcher();
	createVertexBufferForSpriteBatcher();
	createVertexBufferForGeometryBatcher();
	createIndexBuffer();
	createConstantBuffer();
	createMatrix();
}

void DirectXManager::initWindowSizeDependentResources(float width, float height)
{
	// Create a descriptor for the render target buffer.
	CD3D11_TEXTURE2D_DESC renderTargetDesc(
		DXGI_FORMAT_B8G8R8A8_UNORM,
		static_cast<UINT>(width),
		static_cast<UINT>(height),
		1,
		1,
		D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE
		);
	renderTargetDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX | D3D11_RESOURCE_MISC_SHARED_NTHANDLE;

	// Allocate a 2-D surface as the render target buffer.
	m_device->CreateTexture2D(&renderTargetDesc, nullptr, &m_renderTarget);
	m_device->CreateRenderTargetView(m_renderTarget, nullptr, &m_renderTargetView);

	// set the viewport
	D3D11_VIEWPORT viewport = { 0 };
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);

	m_deviceContext->RSSetViewports(1, &viewport);
}

void DirectXManager::prepareForSpriteRendering()
{
	DXManager->m_deviceContext->IASetInputLayout(DXManager->m_sbInputLayout);

	// set the shader objects as the active shaders
	DXManager->m_deviceContext->VSSetShader(DXManager->m_sbVertexShader, nullptr, 0);
	DXManager->m_deviceContext->PSSetShader(DXManager->m_sbPixelShader, nullptr, 0);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	//	Disable GPU access to the vertex buffer data.
	DXManager->m_deviceContext->Map(DXManager->m_sbVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	int numTextureVertices = DXManager->m_textureVertices.size();
	//	Update the vertex buffer here.
	memcpy(mappedResource.pData, &DXManager->m_textureVertices[0], sizeof(TEXTURE_VERTEX)* numTextureVertices);

	//	Reenable GPU access to the vertex buffer data.
	DXManager->m_deviceContext->Unmap(DXManager->m_sbVertexBuffer, 0);

	// Set the vertex and index buffer
	UINT stride = sizeof(TEXTURE_VERTEX);
	UINT offset = 0;
	DXManager->m_deviceContext->IASetVertexBuffers(0, 1, &DXManager->m_sbVertexBuffer, &stride, &offset);
}

void DirectXManager::prepareForGeometryRendering()
{
	m_deviceContext->IASetInputLayout(m_gbInputLayout);

	// set the shader objects as the active shaders
	m_deviceContext->VSSetShader(m_gbVertexShader, nullptr, 0);
	m_deviceContext->PSSetShader(m_gbPixelShader, nullptr, 0);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	//	Disable GPU access to the vertex buffer data.
	m_deviceContext->Map(m_gbVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	//	Update the vertex buffer here.
	memcpy(mappedResource.pData, &m_colorVertices.front(), sizeof(COLOR_VERTEX)* m_colorVertices.size());

	//	Reenable GPU access to the vertex buffer data.
	m_deviceContext->Unmap(m_gbVertexBuffer, 0);

	// Set the vertex buffer
	UINT stride = sizeof(COLOR_VERTEX);
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &m_gbVertexBuffer, &stride, &offset);
}

void DirectXManager::cleanUp()
{
	m_device->Release();
	m_deviceContext->Release();
	m_renderTarget->Release();
	m_renderTargetView->Release();
	m_blendState->Release();
	m_constantbuffer->Release();
	m_indexbuffer->Release();
	m_sbSamplerState->Release();
	m_sbVertexShader->Release();
	m_sbPixelShader->Release();
	m_sbInputLayout->Release();
	m_sbVertexBuffer->Release();
	m_gbVertexShader->Release();
	m_gbPixelShader->Release();
	m_gbInputLayout->Release();
	m_gbVertexBuffer->Release();
}

void DirectXManager::initDeviceResources()
{
	// This flag adds support for surfaces with a different color channel ordering
	// than the API default. It is required for compatibility with Direct2D.
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
	// If the project is in a debug build, enable debugging via SDK Layers with this flag.
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// This array defines the set of DirectX hardware feature levels this app will support.
	// Note the ordering should be preserved.
	// Don't forget to declare your application's minimum required feature level in its
	// description. All applications are assumed to support 9.1 unless otherwise stated.
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3
	};

	// Create the Direct3D 11 API device object and a corresponding context.
	D3D11CreateDevice(
		nullptr, // Specify nullptr to use the default adapter.
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags, // Set set debug and Direct2D compatibility flags.
		featureLevels, // List of feature levels this app can support.
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION, // Always set this to D3D11_SDK_VERSION.
		&m_device, // Returns the Direct3D device created.
		&m_featureLevel, // Returns feature level of device created.
		&m_deviceContext // Returns the device immediate context.
		);
}

void DirectXManager::createBlendState()
{
	D3D11_BLEND_DESC bd;
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	bd.IndependentBlendEnable = FALSE;
	bd.AlphaToCoverageEnable = FALSE;

	m_device->CreateBlendState(&bd, &m_blendState);

	// set the blend state
	m_deviceContext->OMSetBlendState(m_blendState, 0, 0xffffffff);
}

void DirectXManager::createSamplerState()
{
	D3D11_SAMPLER_DESC sd;
	sd.Filter = D3D11_FILTER_ANISOTROPIC;
	sd.MaxAnisotropy = 16;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.BorderColor[0] = 0.0f;
	sd.BorderColor[1] = 0.0f;
	sd.BorderColor[2] = 0.0f;
	sd.BorderColor[3] = 0.0f;
	sd.MinLOD = 0.0f;
	sd.MaxLOD = FLT_MAX;
	sd.MipLODBias = 0.0f;
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // linear filtering
	sd.MinLOD = 5.0f; // mip level 5 will appear blurred

	m_device->CreateSamplerState(&sd, &m_sbSamplerState); // create the linear blur sampler

	// set the appropriate sampler state
	m_deviceContext->PSSetSamplers(0, 1, &m_sbSamplerState);
}

void DirectXManager::createInputLayoutForSpriteBatcher()
{
	// Create a Basic Reader-Writer class to load data from disk.  This class is examined
	// in the Resource Loading sample.
	BasicReaderWriter^ reader = ref new BasicReaderWriter();
	Platform::Array<byte>^ vertexShaderBytecode;
	Platform::Array<byte>^ pixelShaderBytecode;

	// Load the raw shader bytecode from disk and create shader objects with it.
	vertexShaderBytecode = reader->ReadData("TextureVertexShader.cso");
	pixelShaderBytecode = reader->ReadData("TexturePixelShader.cso");

	// initialize input layout
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// create and set the input layout
	m_device->CreateInputLayout(ied, ARRAYSIZE(ied), vertexShaderBytecode->Data, vertexShaderBytecode->Length, &m_sbInputLayout);

	m_device->CreateVertexShader(vertexShaderBytecode->Data, vertexShaderBytecode->Length, nullptr, &m_sbVertexShader);
	m_device->CreatePixelShader(pixelShaderBytecode->Data, pixelShaderBytecode->Length, nullptr, &m_sbPixelShader);
}

void DirectXManager::createInputLayoutForGeometryBatcher()
{
	// Create a Basic Reader - Writer class to load data from disk.This class is examined
	// in the Resource Loading sample.
	BasicReaderWriter^ reader = ref new BasicReaderWriter();
	Platform::Array<byte>^ vertexShaderBytecode;
	Platform::Array<byte>^ pixelShaderBytecode;

	// Load the raw shader bytecode from disk and create shader objects with it.
	vertexShaderBytecode = reader->ReadData("ColorVertexShader.cso");
	pixelShaderBytecode = reader->ReadData("ColorPixelShader.cso");

	// initialize input layout
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// create and set the input layout
	m_device->CreateInputLayout(ied, ARRAYSIZE(ied), vertexShaderBytecode->Data, vertexShaderBytecode->Length, &m_gbInputLayout);

	m_device->CreateVertexShader(vertexShaderBytecode->Data, vertexShaderBytecode->Length, nullptr, &m_gbVertexShader);
	m_device->CreatePixelShader(pixelShaderBytecode->Data, pixelShaderBytecode->Length, nullptr, &m_gbPixelShader);
}

void DirectXManager::createVertexBufferForSpriteBatcher()
{
	m_textureVertices.reserve(MAX_BATCH_SIZE * VERTICES_PER_RECTANGLE);
	TEXTURE_VERTEX tv = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < MAX_BATCH_SIZE * VERTICES_PER_RECTANGLE; i++)
	{
		m_textureVertices.push_back(tv);
	}

	D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	vertexBufferDesc.ByteWidth = sizeof(TEXTURE_VERTEX)* m_textureVertices.size();
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	vertexBufferData.pSysMem = &m_textureVertices[0];
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;

	DX::ThrowIfFailed(m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_sbVertexBuffer));
}

void DirectXManager::createVertexBufferForGeometryBatcher()
{
	m_colorVertices.reserve(MAX_BATCH_SIZE * VERTICES_PER_RECTANGLE);
	COLOR_VERTEX cv = { 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < MAX_BATCH_SIZE * VERTICES_PER_RECTANGLE; i++)
	{
		m_colorVertices.push_back(cv);
	}

	D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	vertexBufferDesc.ByteWidth = sizeof(COLOR_VERTEX)* m_colorVertices.size();
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	vertexBufferData.pSysMem = &m_colorVertices[0];
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;

	DX::ThrowIfFailed(m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_gbVertexBuffer));
}

void DirectXManager::createIndexBuffer()
{
	D3D11_BUFFER_DESC indexBufferDesc = { 0 };

	indexBufferDesc.ByteWidth = sizeof(short)* MAX_BATCH_SIZE * INDICES_PER_RECTANGLE;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	auto indexValues = createIndexValues();

	D3D11_SUBRESOURCE_DATA indexDataDesc = { 0 };

	indexDataDesc.pSysMem = &indexValues.front();

	m_device->CreateBuffer(&indexBufferDesc, &indexDataDesc, &m_indexbuffer);

	m_deviceContext->IASetIndexBuffer(m_indexbuffer, DXGI_FORMAT_R16_UINT, 0);
}

void DirectXManager::createConstantBuffer()
{
	D3D11_BUFFER_DESC bd = { 0 };

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = 64;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	m_device->CreateBuffer(&bd, nullptr, &m_constantbuffer);

	m_deviceContext->VSSetConstantBuffers(0, 1, &m_constantbuffer);
}

void DirectXManager::createMatrix()
{
	using namespace DirectX;

	// calculate the view transformation
	XMVECTOR vecCamPosition = XMVectorSet(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, 0);
	XMVECTOR vecCamLookAt = XMVectorSet(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0);
	XMVECTOR vecCamUp = XMVectorSet(0, 1, 0, 0);
	XMMATRIX matView = XMMatrixLookAtRH(vecCamPosition, vecCamLookAt, vecCamUp);

	// calculate the projection transformation
	XMMATRIX matProjection = XMMatrixOrthographicRH(SCREEN_WIDTH, SCREEN_HEIGHT, -1.0, 1.0);

	// calculate the final matrix
	m_matFinal = matView * matProjection;

	// send the final matrix to video memory
	m_deviceContext->UpdateSubresource(m_constantbuffer, 0, 0, &m_matFinal, 0, 0);
}

std::vector<short> DirectXManager::createIndexValues()
{
	std::vector<short> indices;

	indices.reserve(MAX_BATCH_SIZE * INDICES_PER_RECTANGLE);

	short j = 0;
	for (int i = 0; i < MAX_BATCH_SIZE * INDICES_PER_RECTANGLE; i += INDICES_PER_RECTANGLE, j += VERTICES_PER_RECTANGLE)
	{
		indices.push_back(j);
		indices.push_back(j + 1);
		indices.push_back(j + 2);
		indices.push_back(j + 2);
		indices.push_back(j + 3);
		indices.push_back(j + 0);
	}

	return indices;
}

DirectXManager::DirectXManager()
{
	// Hide Constructor for Singleton
}