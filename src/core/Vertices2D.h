//
//  Vertices2D.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __tappyplane__Vertices2D__
#define __tappyplane__Vertices2D__

extern "C"
{
#include "platform_gl.h"
}

typedef struct {
    GLfloat *vertices;
    GLfloat *textureCoords;
    GLfloat *colors;
} VertexData;

class Vertices2D
{
public:
    Vertices2D(int maxNumVertices, bool isUsingTextureCoordinates, bool isUsingColors);
    
    ~Vertices2D();
    
    void resetIndex();
    
    void addVertexCoordinate(float vc);
    
    void addTextureCoordinate(float tc);
    
    void addColorCoordinate(float cc);
    
    void bind();
    
    void unbind();
    
    void drawPrimitiveType(GLenum mode, int offset, GLshort *indices, int numVertices);

private:
    VertexData m_vertexData;
    int m_iVerticesIndex;
    int m_iTextureCoordsIndex;
    int m_iColorsIndex;
    bool m_hasColor;
    bool m_hasTextureCoordinates;
};

#endif /* defined(__tappyplane__Vertices2D__) */