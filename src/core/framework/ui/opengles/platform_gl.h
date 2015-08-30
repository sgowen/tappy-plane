//
//  platform_gl.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2014 Gowen Game Dev. All rights reserved.
//

#ifndef gowengamedev_platform_gl_h
#define gowengamedev_platform_gl_h

#ifdef GGD_IOS
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif defined GGD_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#endif /* defined(gowengamedev_platform_gl_h) */