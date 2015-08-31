//
//  Direct3DGpuProgramWrapper.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/30/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "pch.h"
#include "Direct3DTextureGpuProgramWrapper.h"
#include "Direct3DManager.h"

Direct3DTextureGpuProgramWrapper::Direct3DTextureGpuProgramWrapper()
{
	// Empty
}

void Direct3DTextureGpuProgramWrapper::bind()
{
	D3DManager->m_deviceContext->IASetInputLayout(D3DManager->m_sbInputLayout);

	// set the shader objects as the active shaders
	D3DManager->m_deviceContext->VSSetShader(D3DManager->m_sbVertexShader, nullptr, 0);
	D3DManager->m_deviceContext->PSSetShader(D3DManager->m_sbPixelShader, nullptr, 0);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	//	Disable GPU access to the vertex buffer data.
	D3DManager->m_deviceContext->Map(D3DManager->m_sbVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	int numTextureVertices = D3DManager->m_textureVertices.size();
	//	Update the vertex buffer here.
	memcpy(mappedResource.pData, &D3DManager->m_textureVertices[0], sizeof(TEXTURE_VERTEX)* numTextureVertices);

	//	Reenable GPU access to the vertex buffer data.
	D3DManager->m_deviceContext->Unmap(D3DManager->m_sbVertexBuffer, 0);

	// Set the vertex and index buffer
	UINT stride = sizeof(TEXTURE_VERTEX);
	UINT offset = 0;
	D3DManager->m_deviceContext->IASetVertexBuffers(0, 1, &D3DManager->m_sbVertexBuffer, &stride, &offset);
}

void Direct3DTextureGpuProgramWrapper::unbind()
{
	// Clear out shader resource, since we are going to be binding to it again for writing on the next frame
	ID3D11ShaderResourceView *pSRV[1] = { NULL };
	D3DManager->m_deviceContext->PSSetShaderResources(0, 1, pSRV);
}