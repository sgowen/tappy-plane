//
//  PuffCloud.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__PuffCloud__
#define __tappyplane__PuffCloud__

#include "PhysicalEntity.h"

class PuffCloud : public PhysicalEntity
{
public:
    PuffCloud(float x, float y, float width, float height, float angle);
    
    void update(float deltaTime);
    
    void shift(float shiftX);
    
    float getAlpha();
    
private:
    float m_fAlpha;
};

#endif /* defined(__tappyplane__PuffCloud__) */