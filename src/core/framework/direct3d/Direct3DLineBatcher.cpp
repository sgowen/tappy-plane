//
//  Direct3DLineBatcher.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/16/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#define VERTICES_PER_LINE 2

#include "pch.h"
#include "Direct3DLineBatcher.h"
#include "BasicReaderWriter.h"
#include "GameConstants.h"
#include "Line.h"
#include "Vector2D.h"
#include "Direct3DProgram.h"
#include "DirectXManager.h"

Direct3DLineBatcher::Direct3DLineBatcher() : LineBatcher()
{
	// Empty
}

void Direct3DLineBatcher::beginBatch()
{
	DXManager->m_colorVertices.clear();
	m_iNumLines = 0;
}

void Direct3DLineBatcher::endBatch()
{
	if (m_iNumLines > 0)
	{
		// set the primitive topology
		DXManager->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		DXManager->prepareForGeometryRendering();

		DXManager->m_deviceContext->Draw(m_iNumLines * VERTICES_PER_LINE, 0);
	}
}

void Direct3DLineBatcher::renderLine(float originX, float originY, float endX, float endY, Color &color)
{
	addVertexCoordinate(originX, originY, 0, color.red, color.green, color.blue, color.alpha, 0, 0);
	addVertexCoordinate(endX, endY, 0, color.red, color.green, color.blue, color.alpha, 0, 0);

	m_iNumLines++;
}

void Direct3DLineBatcher::addVertexCoordinate(float x, float y, float z, float r, float g, float b, float a, float u, float v)
{
	COLOR_VERTEX cv = { x, y, z, r, g, b, a };
	DXManager->m_colorVertices.push_back(cv);
}