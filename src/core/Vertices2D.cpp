//
//  Vertices2D.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "Vertices2D.h"
#include <stdlib.h>

Vertices2D::Vertices2D(int maxNumVertices, bool isUsingTextureCoordinates, bool isUsingColors)
{
    m_vertexData.vertices = new GLfloat[maxNumVertices * 2];
    m_vertexData.textureCoords = new GLfloat[maxNumVertices * 2];
    
    if(isUsingColors)
    {
        m_vertexData.colors = new GLfloat[maxNumVertices * 4];
    }
    
    m_iVerticesIndex = 0;
    m_iTextureCoordsIndex = 0;
    m_iColorsIndex = 0;
    
    m_hasColor = isUsingColors;
    m_hasTextureCoordinates = isUsingTextureCoordinates;
}

Vertices2D::~Vertices2D()
{
    delete[] m_vertexData.vertices;
    delete[] m_vertexData.textureCoords;
    
    if(m_hasColor)
    {
        delete[] m_vertexData.colors;
    }
}

void Vertices2D::resetIndex()
{
    m_iVerticesIndex = 0;
    m_iTextureCoordsIndex = 0;
    m_iColorsIndex = 0;
}

void Vertices2D::addVertexCoordinate(float vc)
{
    m_vertexData.vertices[m_iVerticesIndex++] = vc;
}

void Vertices2D::addTextureCoordinate(float tc)
{
    m_vertexData.textureCoords[m_iTextureCoordsIndex++] = tc;
}

void Vertices2D::addColorCoordinate(float cc)
{
    m_vertexData.colors[m_iColorsIndex++] = cc;
}

void Vertices2D::bind()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, m_vertexData.vertices);
    
    if (m_hasColor)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, 0, m_vertexData.colors);
    }
    
    if (m_hasTextureCoordinates)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, m_vertexData.textureCoords);
    }
}

void Vertices2D::unbind()
{
    if (m_hasTextureCoordinates)
    {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    
    if (m_hasColor)
    {
        glDisableClientState(GL_COLOR_ARRAY);
    }
}

void Vertices2D::drawPrimitiveType(GLenum mode, int offset, GLshort *indices, int numVertices)
{
    if (indices != nullptr)
    {
        glDrawElements(mode, numVertices, GL_UNSIGNED_SHORT, indices);
    }
    else
    {
        glDrawArrays(mode, offset, numVertices);
    }
}