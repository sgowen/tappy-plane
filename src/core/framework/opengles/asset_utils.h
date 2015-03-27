//
//  asset_utils.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef Asset_Utils_H
#define Asset_Utils_H

#include "platform_gl.h"

GLuint load_png_asset_into_texture(const char* relative_path);

GLuint build_program_from_assets(const char* vertex_shader_path, const char* fragment_shader_path);

#endif /* Asset_Utils_H */