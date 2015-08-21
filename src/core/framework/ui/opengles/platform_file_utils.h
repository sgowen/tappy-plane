//
//  platform_file_utils.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef Platform_File_Utils_H
#define Platform_File_Utils_H

typedef struct {
	const long data_length;
	const void *data;
	const void *file_handle;
} FileData;

FileData get_file_data(const char* path);

void release_file_data(const FileData* file_data);

#endif /* Platform_File_Utils_H */