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
#include "Direct3DManager.h"
#include "GpuProgramWrapper.h"

Direct3DCircleBatcher::Direct3DCircleBatcher() : CircleBatcher()
{
	// Empty
}

void Direct3DCircleBatcher::renderCircle(Circle &circle, Color &c)
{
	renderCircle(circle, c, *D3DManager->m_colorProgram);
}

void Direct3DCircleBatcher::renderPartialCircle(Circle &circle, int arcDegrees, Color &c)
{
	renderPartialCircle(circle, arcDegrees, c, *D3DManager->m_colorProgram);
}

void Direct3DCircleBatcher::renderCircle(Circle &circle, Color &c, GpuProgramWrapper &gpuProgramWrapper)
{
	m_iNumPoints = 0;
	D3DManager->m_colorVertices.clear();

	for (int i = 0; i <= 360; i += DEGREE_SPACING)
	{
		float rad = DEGREES_TO_RADIANS(i);
		float cos = cosf(rad);
		float sin = sinf(rad);

		addVertexCoordinate(cos * circle.m_fRadius + circle.getCenter().getX(), sin * circle.m_fRadius + circle.getCenter().getY(), 0, c.red, c.green, c.blue, c.alpha, 0, 0);

		addVertexCoordinate(circle.getCenter().getX(), circle.getCenter().getY(), 0, c.red, c.green, c.blue, c.alpha, 0, 0);
	}

	endBatch(gpuProgramWrapper);
}

void Direct3DCircleBatcher::renderPartialCircle(Circle &circle, int arcDegrees, Color &c, GpuProgramWrapper &gpuProgramWrapper)
{
	m_iNumPoints = 0;
	D3DManager->m_colorVertices.clear();

	for (int i = 90; i < (450 - arcDegrees); i += DEGREE_SPACING)
	{
		float rad = DEGREES_TO_RADIANS(i);
		float cos = cosf(rad);
		float sin = sinf(rad);

		addVertexCoordinate(cos * circle.m_fRadius + circle.getCenter().getX(), sin * circle.m_fRadius + circle.getCenter().getY(), 0, c.red, c.green, c.blue, c.alpha, 0, 0);

		addVertexCoordinate(circle.getCenter().getX(), circle.getCenter().getY(), 0, c.red, c.green, c.blue, c.alpha, 0, 0);
	}

	float rad = DEGREES_TO_RADIANS(450 - arcDegrees);
	float cos = cosf(rad);
	float sin = sinf(rad);

	addVertexCoordinate(cos * circle.m_fRadius + circle.getCenter().getX(), sin * circle.m_fRadius + circle.getCenter().getY(), 0, c.red, c.green, c.blue, c.alpha, 0, 0);

	addVertexCoordinate(circle.getCenter().getX(), circle.getCenter().getY(), 0, c.red, c.green, c.blue, c.alpha, 0, 0);

	endBatch(gpuProgramWrapper);
}

void Direct3DCircleBatcher::endBatch(GpuProgramWrapper &gpuProgramWrapper)
{
	// set the primitive topology
	D3DManager->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	gpuProgramWrapper.bind();

	D3DManager->m_deviceContext->Draw(m_iNumPoints, 0);

	gpuProgramWrapper.unbind();
}

void Direct3DCircleBatcher::addVertexCoordinate(float x, float y, float z, float r, float g, float b, float a, float u, float v)
{
	COLOR_VERTEX cv = { x, y, z, r, g, b, a };
	D3DManager->m_colorVertices.push_back(cv);

	m_iNumPoints++;
}