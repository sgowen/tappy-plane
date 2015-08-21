//
//  Glove.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__Glove__
#define __tappyplane__Glove__

#include "PhysicalEntity.h"

class Glove : public PhysicalEntity
{
public:
    Glove(float x, float y, float width, float height);
    
    void update(float deltaTime);
};

#endif /* defined(__tappyplane__Glove__) */