//
//  PuffCloud.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __tappyplane__PuffCloud__
#define __tappyplane__PuffCloud__

#include "GameObject.h"

class PuffCloud : public GameObject
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