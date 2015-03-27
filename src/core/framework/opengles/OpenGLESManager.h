//
//  OpenGLESManager.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/19/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__OpenGLESManager__
#define __gowengamedev__OpenGLESManager__

#define MAX_BATCH_SIZE 1024
#define VERTICES_PER_RECTANGLE 4
#define INDICES_PER_RECTANGLE 6

#define OGLESManager (OpenGLESManager::getInstance())

extern "C"
{
#include "platform_gl.h"
#include "linmath.h"
}

#include "OpenGLESProgram.h"

#include <vector>

class OpenGLESManager
{
public:
    std::vector<GLfloat> m_textureVertices;
    std::vector<GLfloat> m_colorVertices;
    
    std::vector<GLshort> m_indices;
    
    TextureProgram m_textureProgram;
    ColorProgram m_colorProgram;
    
    GLuint sb_vbo_object; // For Sprite Batcher
    GLuint gb_vbo_object; // For Geometry Batcher
    
    mat4x4 m_viewMatrix;
    mat4x4 m_projectionMatrix;
    mat4x4 m_viewProjectionMatrix;
    
    static OpenGLESManager * getInstance();
    
    void init(int width, int height);
    
    // Called by Batchers
    void addVertexCoordinate(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat u, GLfloat v);
    void addVertexCoordinate(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void prepareForSpriteRendering();
    void prepareForGeometryRendering();
    void finishSpriteRendering();
    void finishGeometryRendering();
    
private:
    void buildShaderPrograms();
    void generateIndices();
    void createMatrix();
    
    OpenGLESManager();
};

#endif /* defined(__gowengamedev__OpenGLESManager__) */