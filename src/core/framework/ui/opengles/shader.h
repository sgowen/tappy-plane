//
//  shader.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 9/29/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef Shader_H
#define Shader_H

#include "platform_gl.h"

GLuint compile_shader(const GLenum type, const GLchar* source, const GLint length);

GLuint link_program(const GLuint vertex_shader, const GLuint fragment_shader);

GLuint build_program(const GLchar * vertex_shader_source, const GLint vertex_shader_source_length, const GLchar * fragment_shader_source, const GLint fragment_shader_source_length);

/* Should be called just before using a program to draw, if validation is needed. */
GLint validate_program(const GLuint program);

#endif /* Shader_H */