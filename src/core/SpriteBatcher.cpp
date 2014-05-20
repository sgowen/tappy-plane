//
//  SpriteBatcher.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "SpriteBatcher.h"
#include <stdlib.h>
#include "Vertices2D.h"
#include "TextureRegion.h"
#include "Color.h"

SpriteBatcher::SpriteBatcher(int maxSprites, bool useColors)
{
    m_vertices = std::unique_ptr<Vertices2D>(new Vertices2D(maxSprites, true, useColors));
    m_iNumSprites = 0;
    
    generateIndices(maxSprites);
}

SpriteBatcher::~SpriteBatcher()
{
    delete[] m_indices;
}

void SpriteBatcher::beginBatch()
{
    m_vertices->resetIndex();
    m_iNumSprites = 0;
}

void SpriteBatcher::endBatchWithTexture(GLuint &texture)
{
    if(m_iNumSprites > 0)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        m_vertices->bind();
        m_vertices->drawPrimitiveType(GL_TRIANGLES, 0, m_indices, m_iNumSprites * 6);
        m_vertices->unbind();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void SpriteBatcher::drawSprite(float x, float y, float width, float height, float angle, TextureRegion tr)
{
    if(angle > 0)
    {
        float halfWidth = width / 2;
        float halfHeight = height / 2;
        
        float rad = DEGREES_TO_RADIANS(angle);
        float cos = cosf(rad);
        float sin = sinf(rad);
        
        float x1 = -halfWidth * cos - (-halfHeight) * sin;
        float y1 = -halfWidth * sin + (-halfHeight) * cos;
        
        float x2 = halfWidth * cos - (-halfHeight) * sin;
        float y2 = halfWidth * sin + (-halfHeight) * cos;
        
        float x3 = halfWidth * cos - halfHeight * sin;
        float y3 = halfWidth * sin + halfHeight * cos;
        
        float x4 = -halfWidth * cos - halfHeight * sin;
        float y4 = -halfWidth * sin + halfHeight * cos;
        
        x1 += x;
        y1 += y;
        
        x2 += x;
        y2 += y;
        
        x3 += x;
        y3 += y;
        
        x4 += x;
        y4 += y;
        
        m_vertices->addVertexCoordinate(x1);
        m_vertices->addVertexCoordinate(y1);
        m_vertices->addTextureCoordinate(tr.u1);
        m_vertices->addTextureCoordinate(tr.v2);
        
        m_vertices->addVertexCoordinate(x2);
        m_vertices->addVertexCoordinate(y2);
        m_vertices->addTextureCoordinate(tr.u2);
        m_vertices->addTextureCoordinate(tr.v2);
        
        m_vertices->addVertexCoordinate(x3);
        m_vertices->addVertexCoordinate(y3);
        m_vertices->addTextureCoordinate(tr.u2);
        m_vertices->addTextureCoordinate(tr.v1);
        
        m_vertices->addVertexCoordinate(x4);
        m_vertices->addVertexCoordinate(y4);
        m_vertices->addTextureCoordinate(tr.u1);
        m_vertices->addTextureCoordinate(tr.v1);
    }
    else
    {
        drawSprite(x, y, width, height, tr);
    }
    
    m_iNumSprites++;
}

void SpriteBatcher::drawSprite(float x, float y, float width, float height, float angle, Color &color, TextureRegion tr)
{
    if(angle > 0)
    {
        float halfWidth = width / 2;
        float halfHeight = height / 2;
        
        float rad = DEGREES_TO_RADIANS(angle);
        float cos = cosf(rad);
        float sin = sinf(rad);
        
        float x1 = -halfWidth * cos - (-halfHeight) * sin;
        float y1 = -halfWidth * sin + (-halfHeight) * cos;
        
        float x2 = halfWidth * cos - (-halfHeight) * sin;
        float y2 = halfWidth * sin + (-halfHeight) * cos;
        
        float x3 = halfWidth * cos - halfHeight * sin;
        float y3 = halfWidth * sin + halfHeight * cos;
        
        float x4 = -halfWidth * cos - halfHeight * sin;
        float y4 = -halfWidth * sin + halfHeight * cos;
        
        x1 += x;
        y1 += y;
        
        x2 += x;
        y2 += y;
        
        x3 += x;
        y3 += y;
        
        x4 += x;
        y4 += y;
        
        m_vertices->addVertexCoordinate(x1);
        m_vertices->addVertexCoordinate(y1);
        addColorCoordinates(color);
        m_vertices->addTextureCoordinate(tr.u1);
        m_vertices->addTextureCoordinate(tr.v2);
        
        m_vertices->addVertexCoordinate(x2);
        m_vertices->addVertexCoordinate(y2);
        addColorCoordinates(color);
        m_vertices->addTextureCoordinate(tr.u2);
        m_vertices->addTextureCoordinate(tr.v2);
        
        m_vertices->addVertexCoordinate(x3);
        m_vertices->addVertexCoordinate(y3);
        addColorCoordinates(color);
        m_vertices->addTextureCoordinate(tr.u2);
        m_vertices->addTextureCoordinate(tr.v1);
        
        m_vertices->addVertexCoordinate(x4);
        m_vertices->addVertexCoordinate(y4);
        addColorCoordinates(color);
        m_vertices->addTextureCoordinate(tr.u1);
        m_vertices->addTextureCoordinate(tr.v1);
    }
    else
    {
        drawSprite(x, y, width, height, color, tr);
    }
    
    m_iNumSprites++;
}

#pragma private methods

void SpriteBatcher::drawSprite(float x, float y, float width, float height, TextureRegion tr)
{
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    GLfloat x1 = x - halfWidth;
    GLfloat y1 = y - halfHeight;
    GLfloat x2 = x + halfWidth;
    GLfloat y2 = y + halfHeight;
    
    m_vertices->addVertexCoordinate(x1);
    m_vertices->addVertexCoordinate(y1);
    m_vertices->addTextureCoordinate(tr.u1);
    m_vertices->addTextureCoordinate(tr.v2);
    
    m_vertices->addVertexCoordinate(x2);
    m_vertices->addVertexCoordinate(y1);
    m_vertices->addTextureCoordinate(tr.u2);
    m_vertices->addTextureCoordinate(tr.v2);
    
    m_vertices->addVertexCoordinate(x2);
    m_vertices->addVertexCoordinate(y2);
    m_vertices->addTextureCoordinate(tr.u2);
    m_vertices->addTextureCoordinate(tr.v1);
    
    m_vertices->addVertexCoordinate(x1);
    m_vertices->addVertexCoordinate(y2);
    m_vertices->addTextureCoordinate(tr.u1);
    m_vertices->addTextureCoordinate(tr.v1);
}

void SpriteBatcher::drawSprite(float x, float y, float width, float height, Color &color, TextureRegion tr)
{
    GLfloat halfWidth = width / 2;
    GLfloat halfHeight = height / 2;
    GLfloat x1 = x - halfWidth;
    GLfloat y1 = y - halfHeight;
    GLfloat x2 = x + halfWidth;
    GLfloat y2 = y + halfHeight;
    
    m_vertices->addVertexCoordinate(x1);
    m_vertices->addVertexCoordinate(y1);
    addColorCoordinates(color);
    m_vertices->addTextureCoordinate(tr.u1);
    m_vertices->addTextureCoordinate(tr.v2);
    
    m_vertices->addVertexCoordinate(x2);
    m_vertices->addVertexCoordinate(y1);
    addColorCoordinates(color);
    m_vertices->addTextureCoordinate(tr.u2);
    m_vertices->addTextureCoordinate(tr.v2);
    
    m_vertices->addVertexCoordinate(x2);
    m_vertices->addVertexCoordinate(y2);
    addColorCoordinates(color);
    m_vertices->addTextureCoordinate(tr.u2);
    m_vertices->addTextureCoordinate(tr.v1);
    
    m_vertices->addVertexCoordinate(x1);
    m_vertices->addVertexCoordinate(y2);
    addColorCoordinates(color);
    m_vertices->addTextureCoordinate(tr.u1);
    m_vertices->addTextureCoordinate(tr.v1);
}

void SpriteBatcher::addColorCoordinates(Color &color)
{
    m_vertices->addColorCoordinate(color.red);
    m_vertices->addColorCoordinate(color.green);
    m_vertices->addColorCoordinate(color.blue);
    m_vertices->addColorCoordinate(color.alpha);
}

void SpriteBatcher::generateIndices(int maxSprites)
{
    int numIndices = maxSprites * 6;
    m_indices = new GLshort[numIndices];
    
    GLshort j = 0;
    
    for (int i = 0; i < numIndices; i += 6, j += 4)
    {
        m_indices[i + 0] = j + 0;
        m_indices[i + 1] = j + 1;
        m_indices[i + 2] = j + 2;
        m_indices[i + 3] = j + 2;
        m_indices[i + 4] = j + 3;
        m_indices[i + 5] = j + 0;
    }
}