//
//  platform_asset_utils.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef Platform_Asset_Utils_H
#define Platform_Asset_Utils_H

#include "platform_file_utils.h"

FileData get_asset_data(const char* relative_path);

void release_asset_data(const FileData* file_data);

#endif /* Platform_Asset_Utils_H */