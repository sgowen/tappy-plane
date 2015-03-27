//
//  Direct3DProgram.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/16/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__Direct3DProgram__
#define __gowengamedev__Direct3DProgram__

struct COLOR_VERTEX
{
	float X, Y, Z; // vertex position
	float R, G, B, A; // vertex color
};

struct TEXTURE_VERTEX
{
	float X, Y, Z; // vertex position
	float R, G, B, A; // vertex color
	float U, V;    // texture coordinates
};

#endif /* defined(__gowengamedev__Direct3DProgram__) */
