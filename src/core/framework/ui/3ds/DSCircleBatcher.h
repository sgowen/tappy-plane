//
//  DSCircleBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/25/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__DSCircleBatcher__
#define __gowengamedev__DSCircleBatcher__

#include "CircleBatcher.h"

class DSCircleBatcher : public CircleBatcher
{
public:
    DSCircleBatcher();
    
    virtual void renderCircle(Circle &circle, Color &color);
    
    virtual void renderPartialCircle(Circle &circle, int arcDegrees, Color &color);
    
private:
    void endBatch(int numPoints);
};

#endif /* defined(__gowengamedev__DSCircleBatcher__) */
