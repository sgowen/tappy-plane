//
//  platform_file_utils.h
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
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