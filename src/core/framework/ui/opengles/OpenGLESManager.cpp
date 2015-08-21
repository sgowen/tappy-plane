//
//  OpenGLESManager.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/19/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "OpenGLESManager.h"
#include "macros.h"
#include <assert.h>

extern "C"
{
#include "asset_utils.h"
}

OpenGLESManager * OpenGLESManager::getInstance()
{
    static OpenGLESManager *openGLESManager = new OpenGLESManager();
    return openGLESManager;
}

void OpenGLESManager::init(int width, int height, float gameWidth, float gameHeight)
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_screenFBO);
    
    glViewport(0, 0, width, height);
    glScissor(0, 0, width, height);
    
    buildShaderPrograms();
    generateIndices();
    
    createMatrix(gameWidth, gameHeight);
    
    createFrameBufferObject(width, height);
}

void OpenGLESManager::addVertexCoordinate(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat u, GLfloat v)
{
    m_textureVertices.push_back(x);
    m_textureVertices.push_back(y);
    m_textureVertices.push_back(z);
    m_textureVertices.push_back(r);
    m_textureVertices.push_back(g);
    m_textureVertices.push_back(b);
    m_textureVertices.push_back(a);
    m_textureVertices.push_back(u);
    m_textureVertices.push_back(v);
}

void OpenGLESManager::addVertexCoordinate(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    m_colorVertices.push_back(x);
    m_colorVertices.push_back(y);
    m_colorVertices.push_back(z);
    m_colorVertices.push_back(r);
    m_colorVertices.push_back(g);
    m_colorVertices.push_back(b);
    m_colorVertices.push_back(a);
}

void OpenGLESManager::prepareForSpriteRendering()
{
    glUseProgram(m_textureProgram.program);
    
    glUniformMatrix4fv(m_textureProgram.u_mvp_matrix_location, 1, GL_FALSE, (GLfloat*)m_viewProjectionMatrix);
    glUniform1i(m_textureProgram.u_texture_unit_location, 0);
    
    glGenBuffers(1, &sb_vbo_object);
    glBindBuffer(GL_ARRAY_BUFFER, sb_vbo_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_textureVertices.size(), &m_textureVertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(m_textureProgram.a_position_location, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(0));
    glVertexAttribPointer(m_textureProgram.a_color_location, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(3 * sizeof(GL_FLOAT)));
    glVertexAttribPointer(m_textureProgram.a_texture_coordinates_location, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(7 * sizeof(GL_FLOAT)));
    
    glEnableVertexAttribArray(m_textureProgram.a_position_location);
    glEnableVertexAttribArray(m_textureProgram.a_color_location);
    glEnableVertexAttribArray(m_textureProgram.a_texture_coordinates_location);
}

void OpenGLESManager::prepareForGeometryRendering()
{
    glUseProgram(m_colorProgram.program);
    
    glUniformMatrix4fv(m_colorProgram.u_mvp_matrix_location, 1, GL_FALSE, (GLfloat*)m_viewProjectionMatrix);
    
    glGenBuffers(1, &gb_vbo_object);
    glBindBuffer(GL_ARRAY_BUFFER, gb_vbo_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_colorVertices.size(), &m_colorVertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(m_colorProgram.a_position_location, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, BUFFER_OFFSET(0));
    glVertexAttribPointer(m_colorProgram.a_color_location, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, BUFFER_OFFSET(3 * sizeof(GL_FLOAT)));
    
    glEnableVertexAttribArray(m_colorProgram.a_position_location);
    glEnableVertexAttribArray(m_colorProgram.a_color_location);
}

void OpenGLESManager::finishSpriteRendering()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glDeleteBuffers(1, &sb_vbo_object);
    
    glUseProgram(0);
}

void OpenGLESManager::finishGeometryRendering()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glDeleteBuffers(1, &gb_vbo_object);
    
    glUseProgram(0);
}

#pragma mark <Private>

void OpenGLESManager::buildShaderPrograms()
{
    m_textureProgram = TextureProgram::getTextureProgram(build_program_from_assets("texture_shader.vsh", "texture_shader.fsh"));
    m_colorProgram = ColorProgram::getColorProgram(build_program_from_assets("color_shader.vsh", "color_shader.fsh"));
}

void OpenGLESManager::generateIndices()
{
    m_indices.reserve(MAX_BATCH_SIZE * INDICES_PER_RECTANGLE);
    
    GLshort j = 0;
    for (int i = 0; i < MAX_BATCH_SIZE * INDICES_PER_RECTANGLE; i += INDICES_PER_RECTANGLE, j += VERTICES_PER_RECTANGLE)
    {
        m_indices.push_back(j);
        m_indices.push_back(j + 1);
        m_indices.push_back(j + 2);
        m_indices.push_back(j + 2);
        m_indices.push_back(j + 3);
        m_indices.push_back(j + 0);
    }
}

void OpenGLESManager::createMatrix(float gameWidth, float gameHeight)
{
    vec3 eye = { 0, 0, 1 };
    vec3 center = { 0, 0, 0 };
    vec3 up = { 0, 1, 0 };
    
    mat4x4_ortho(m_projectionMatrix, 0, gameWidth, 0, gameHeight, -1, 1);
    mat4x4_look_at(m_viewMatrix, eye, center, up);
    
    mat4x4_mul(m_viewProjectionMatrix, m_projectionMatrix, m_viewMatrix);
}

void OpenGLESManager::createFrameBufferObject(int width, int height)
{
    // Texture
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &fbo_texture);
    glBindTexture(GL_TEXTURE_2D, fbo_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Framebuffer
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);
    
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_screenFBO);
    
    assert(status == GL_FRAMEBUFFER_COMPLETE);
}

OpenGLESManager::OpenGLESManager()
{
    // Hide Constructor for Singleton
}

OpenGLESManager::~OpenGLESManager()
{
    glDeleteTextures(1, &fbo_texture);
    glDeleteFramebuffers(1, &fbo);
}
