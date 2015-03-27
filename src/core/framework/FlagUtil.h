//
//  FlagUtil.h
//  game-framework
//
//  Created by Stephen Gowen on 8/6/13.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__FlagUtil__
#define __gowengamedev__FlagUtil__

class FlagUtil
{
public:
    static bool isFlagSet(int value, int flag)
	{
		return (value & flag) == flag;
	}
    
    static int setFlag(int value, int flag)
	{
		return value | flag;
	}
    
    static int removeFlag(int value, int flag)
	{
		return value & ~flag;
	}
};

#endif /* defined(__gowengamedev__FlagUtil__) */