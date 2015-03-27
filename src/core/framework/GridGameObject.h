//
//  GridGameObject.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 5/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__GridGameObject__
#define __gowengamedev__GridGameObject__

#include "GameObject.h"

class GridGameObject : public GameObject
{
protected:
    int m_gridX;
    int m_gridY;
    
public:
    GridGameObject(int gridX, int gridY, float width, float height, float angle);
    
    int getGridX();
    
    int getGridY();
};

#endif /* defined(__gowengamedev__GridGameObject__) */