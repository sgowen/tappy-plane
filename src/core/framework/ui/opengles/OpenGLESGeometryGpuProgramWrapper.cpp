//
//  OpenGLESGeometryGpuProgramWrapper.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/27/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "OpenGLESGeometryGpuProgramWrapper.h"
#include "OpenGLESManager.h"
#include "macros.h"

OpenGLESGeometryGpuProgramWrapper::OpenGLESGeometryGpuProgramWrapper(ColorProgramStruct colorProgramStruct) : m_colorProgram(colorProgramStruct)
{
    // Empty
}

void OpenGLESGeometryGpuProgramWrapper::bind()
{
    glUseProgram(m_colorProgram.program);
    
    glUniformMatrix4fv(m_colorProgram.u_mvp_matrix_location, 1, GL_FALSE, (GLfloat*)OGLESManager->m_viewProjectionMatrix);
    
    glGenBuffers(1, &OGLESManager->gb_vbo_object);
    glBindBuffer(GL_ARRAY_BUFFER, OGLESManager->gb_vbo_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * OGLESManager->m_colorVertices.size(), &OGLESManager->m_colorVertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(m_colorProgram.a_position_location, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, BUFFER_OFFSET(0));
    glVertexAttribPointer(m_colorProgram.a_color_location, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, BUFFER_OFFSET(3 * sizeof(GL_FLOAT)));
    
    glEnableVertexAttribArray(m_colorProgram.a_position_location);
    glEnableVertexAttribArray(m_colorProgram.a_color_location);
}

void OpenGLESGeometryGpuProgramWrapper::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glDeleteBuffers(1, &OGLESManager->gb_vbo_object);
    
    glUseProgram(0);
}