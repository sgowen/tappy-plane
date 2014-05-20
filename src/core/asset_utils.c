//
//  asset_utils.c
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "asset_utils.h"
#include "image.h"
#include "platform_asset_utils.h"
#include "texture.h"
#include <assert.h>
#include <stdlib.h>

GLuint load_png_asset_into_texture(const char* relative_path)
{
	assert(relative_path != NULL);

	const FileData png_file = get_asset_data(relative_path);
	const RawImageData raw_image_data = get_raw_image_data_from_png(png_file.data, png_file.data_length);
	const GLuint texture_object_id = load_texture(raw_image_data.width, raw_image_data.height, raw_image_data.gl_color_format, raw_image_data.data);

	release_raw_image_data(&raw_image_data);
	release_asset_data(&png_file);

	return texture_object_id;
}