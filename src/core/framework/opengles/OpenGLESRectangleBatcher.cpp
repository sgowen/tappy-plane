//
//  OpenGLESRectangleBatcher.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 7/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "OpenGLESRectangleBatcher.h"
#include "macros.h"
#include "Rectangle.h"
#include "Vector2D.h"
#include "OpenGLESManager.h"

OpenGLESRectangleBatcher::OpenGLESRectangleBatcher(bool isFill) : RectangleBatcher(isFill)
{
    m_iNumRectangles = 0;
}

void OpenGLESRectangleBatcher::beginBatch()
{
    OGLESManager->m_colorVertices.clear();
    m_iNumRectangles = 0;
}

void OpenGLESRectangleBatcher::endBatch()
{
    if (m_iNumRectangles > 0)
    {
        OGLESManager->prepareForGeometryRendering();
        
        glDrawElements(m_isFill ? GL_TRIANGLES : GL_LINE_STRIP, m_iNumRectangles * INDICES_PER_RECTANGLE, GL_UNSIGNED_SHORT, &OGLESManager->m_indices[0]);
        
        OGLESManager->finishGeometryRendering();
    }
}

void OpenGLESRectangleBatcher::renderRectangle(float x1, float y1, float x2, float y2, Color &color)
{
    OGLESManager->addVertexCoordinate(x1, y1, 0, color.red, color.green, color.blue, color.alpha);
    OGLESManager->addVertexCoordinate(x1, y2, 0, color.red, color.green, color.blue, color.alpha);
    OGLESManager->addVertexCoordinate(x2, y2, 0, color.red, color.green, color.blue, color.alpha);
    OGLESManager->addVertexCoordinate(x2, y1, 0, color.red, color.green, color.blue, color.alpha);
    
    m_iNumRectangles++;
}