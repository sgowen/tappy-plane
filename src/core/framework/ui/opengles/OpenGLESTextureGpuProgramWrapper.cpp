//
//  OpenGLESGpuProgramWrapper.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/27/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "OpenGLESTextureGpuProgramWrapper.h"
#include "OpenGLESManager.h"
#include "macros.h"

OpenGLESTextureGpuProgramWrapper::OpenGLESTextureGpuProgramWrapper(TextureProgramStruct textureProgramStruct) : m_textureProgram(textureProgramStruct)
{
    // Empty
}

void OpenGLESTextureGpuProgramWrapper::bind()
{
    glUseProgram(m_textureProgram.program);
    
    glUniformMatrix4fv(m_textureProgram.u_mvp_matrix_location, 1, GL_FALSE, (GLfloat*)OGLESManager->m_viewProjectionMatrix);
    glUniform1i(m_textureProgram.u_texture_unit_location, 0);
    
    glGenBuffers(1, &OGLESManager->sb_vbo_object);
    glBindBuffer(GL_ARRAY_BUFFER, OGLESManager->sb_vbo_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * OGLESManager->m_textureVertices.size(), &OGLESManager->m_textureVertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(m_textureProgram.a_position_location, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(0));
    glVertexAttribPointer(m_textureProgram.a_color_location, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(3 * sizeof(GL_FLOAT)));
    glVertexAttribPointer(m_textureProgram.a_texture_coordinates_location, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(7 * sizeof(GL_FLOAT)));
    
    glEnableVertexAttribArray(m_textureProgram.a_position_location);
    glEnableVertexAttribArray(m_textureProgram.a_color_location);
    glEnableVertexAttribArray(m_textureProgram.a_texture_coordinates_location);
}

void OpenGLESTextureGpuProgramWrapper::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glDeleteBuffers(1, &OGLESManager->sb_vbo_object);
    
    glUseProgram(0);
}