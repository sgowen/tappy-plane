//
//  Glove.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __tappyplane__Glove__
#define __tappyplane__Glove__

#include "GameObject.h"

class Glove : public GameObject
{
public:
    Glove(float x, float y, float width, float height);
    
    void update(float deltaTime);
    
    float getStateTime();
    
private:
    float m_fStateTime;
};

#endif /* defined(__tappyplane__Glove__) */