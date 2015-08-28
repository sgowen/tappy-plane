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
#include "GpuProgramWrapper.h"

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
    endBatch(*OGLESManager->m_colorProgram);
}

void OpenGLESRectangleBatcher::endBatch(GpuProgramWrapper &gpuProgramWrapper)
{
    if (m_iNumRectangles > 0)
    {
        gpuProgramWrapper.bind();

        glDrawElements(m_isFill ? GL_TRIANGLES : GL_LINE_STRIP, m_iNumRectangles * INDICES_PER_RECTANGLE, GL_UNSIGNED_SHORT, &OGLESManager->m_indices[0]);

        gpuProgramWrapper.unbind();
    }
}

void OpenGLESRectangleBatcher::renderRectangle(float x1, float y1, float x2, float y2, Color &c)
{
    OGLESManager->addVertexCoordinate(x1, y1, 0, c.red, c.green, c.blue, c.alpha);
    OGLESManager->addVertexCoordinate(x1, y2, 0, c.red, c.green, c.blue, c.alpha);
    OGLESManager->addVertexCoordinate(x2, y2, 0, c.red, c.green, c.blue, c.alpha);
    OGLESManager->addVertexCoordinate(x2, y1, 0, c.red, c.green, c.blue, c.alpha);

    m_iNumRectangles++;
}