//
//  Triangle.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__Triangle__
#define __gowengamedev__Triangle__

#include <memory>
#include "Line.h"
#include "Vector2D.h"

class Triangle
{
public:
    Triangle(float x1, float y1, float x2, float y2, float x3, float y3);
    
    void update(float x1, float y1, float x2, float y2, float x3, float y3);
    
    Vector2D& getPointA();
    
    Vector2D& getPointB();
    
    Vector2D& getPointC();
    
    Line& getSideA();
    
    Line& getSideB();
    
    Line& getSideC();
    
private:
    std::unique_ptr<Line> m_sideA;
    std::unique_ptr<Line> m_sideB;
    std::unique_ptr<Line> m_sideC;
};

#endif /* defined(__gowengamedev__Triangle__) */
