//
//  Color.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__Color__
#define __gowengamedev__Color__

struct Color
{
    float red;
    float green;
    float blue;
    float alpha;

	Color(float redIn, float greenIn, float blueIn, float alphaIn) : red(redIn), green(greenIn), blue(blueIn), alpha(alphaIn)
	{
		// Empty
	}
};

#endif /* defined(__gowengamedev__Color__) */
