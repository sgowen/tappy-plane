//
//  Direct3DCircleBatcher.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/16/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#define DEGREE_SPACING 6

#include "pch.h"
#include "Direct3DCircleBatcher.h"
#include "BasicReaderWriter.h"
#include "GameConstants.h"
#include "Circle.h"
#include "Vector2D.h"
#include "Direct3DProgram.h"
#include "macros.h"
#include "DirectXManager.h"

Direct3DCircleBatcher::Direct3DCircleBatcher() : CircleBatcher()
{
	m_iNumPoints = 0;
}

void Direct3DCircleBatcher::renderCircle(Circle &circle, Color &color)
{
	m_iNumPoints = 0;
	DXManager->m_colorVertices.clear();

	for (int i = 0; i <= 360; i += DEGREE_SPACING)
	{
		float rad = DEGREES_TO_RADIANS(i);
		float cos = cosf(rad);
		float sin = sinf(rad);

		addVertexCoordinate(cos * circle.m_fRadius + circle.getCenter().getX(), sin * circle.m_fRadius + circle.getCenter().getY(), 0, color.red, color.green, color.blue, color.alpha, 0, 0);

		addVertexCoordinate(circle.getCenter().getX(), circle.getCenter().getY(), 0, color.red, color.green, color.blue, color.alpha, 0, 0);
	}

	endBatch();
}

void Direct3DCircleBatcher::renderPartialCircle(Circle &circle, int arcDegrees, Color &color)
{
	m_iNumPoints = 0;
	DXManager->m_colorVertices.clear();

	for (int i = 90; i < (450 - arcDegrees); i += DEGREE_SPACING)
	{
		float rad = DEGREES_TO_RADIANS(i);
		float cos = cosf(rad);
		float sin = sinf(rad);

		addVertexCoordinate(cos * circle.m_fRadius + circle.getCenter().getX(), sin * circle.m_fRadius + circle.getCenter().getY(), 0, color.red, color.green, color.blue, color.alpha, 0, 0);

		addVertexCoordinate(circle.getCenter().getX(), circle.getCenter().getY(), 0, color.red, color.green, color.blue, color.alpha, 0, 0);
	}

	float rad = DEGREES_TO_RADIANS(450 - arcDegrees);
	float cos = cosf(rad);
	float sin = sinf(rad);

	addVertexCoordinate(cos * circle.m_fRadius + circle.getCenter().getX(), sin * circle.m_fRadius + circle.getCenter().getY(), 0, color.red, color.green, color.blue, color.alpha, 0, 0);

	addVertexCoordinate(circle.getCenter().getX(), circle.getCenter().getY(), 0, color.red, color.green, color.blue, color.alpha, 0, 0);

	endBatch();
}

void Direct3DCircleBatcher::endBatch()
{
	// set the primitive topology
	DXManager->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	DXManager->prepareForGeometryRendering();

	DXManager->m_deviceContext->Draw(m_iNumPoints, 0);
}

void Direct3DCircleBatcher::addVertexCoordinate(float x, float y, float z, float r, float g, float b, float a, float u, float v)
{
	COLOR_VERTEX cv = { x, y, z, r, g, b, a };
	DXManager->m_colorVertices.push_back(cv);

	m_iNumPoints++;
}