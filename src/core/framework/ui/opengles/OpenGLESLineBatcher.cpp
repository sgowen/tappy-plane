//
//  OpenGLESLineBatcher.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#define VERTICES_PER_LINE 2

#include "OpenGLESLineBatcher.h"
#include "macros.h"
#include "Line.h"
#include "Vector2D.h"
#include "OpenGLESManager.h"
#include "GpuProgramWrapper.h"

OpenGLESLineBatcher::OpenGLESLineBatcher() : LineBatcher()
{
    m_iNumLines = 0;
}

void OpenGLESLineBatcher::beginBatch()
{
    OGLESManager->m_colorVertices.clear();
    m_iNumLines = 0;
}

void OpenGLESLineBatcher::endBatch()
{
    endBatch(*OGLESManager->m_colorProgram);
}

void OpenGLESLineBatcher::endBatch(GpuProgramWrapper &gpuProgramWrapper)
{
    if (m_iNumLines > 0)
    {
        gpuProgramWrapper.bind();
        
        glDrawArrays(GL_LINES, 0, VERTICES_PER_LINE * m_iNumLines);
        
        gpuProgramWrapper.unbind();
    }
}

void OpenGLESLineBatcher::renderLine(float originX, float originY, float endX, float endY, Color &c)
{
    OGLESManager->addVertexCoordinate(originX, originY, 0, c.red, c.green, c.blue, c.alpha);
    OGLESManager->addVertexCoordinate(endX, endY, 0, c.red, c.green, c.blue, c.alpha);
    
    m_iNumLines++;
}