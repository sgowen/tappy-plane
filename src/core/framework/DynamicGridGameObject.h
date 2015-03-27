//
//  DynamicGridGameObject.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 5/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__DynamicGridGameObject__
#define __gowengamedev__DynamicGridGameObject__

#include "DynamicGameObject.h"

class DynamicGridGameObject : public DynamicGameObject
{
protected:
    int m_gridX;
    int m_gridY;
    
public:
    DynamicGridGameObject(int gridX, int gridY, float width, float height, float angle);
    
    virtual Rectangle & getBoundsForGridLogic();
    
    void updateGrid();
    
    void setGridX(int gridX);
    
    int getGridX();
    
    void setGridY(int gridY);
    
    int getGridY();
};

#endif /* defined(__gowengamedev__DynamicGridGameObject__) */