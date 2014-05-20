//
//  Triangle.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/20/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __tappyplane__Triangle__
#define __tappyplane__Triangle__

#include <memory>
#include "Line.h"

class Triangle
{
public:
    Triangle(float x1, float y1, float x2, float y2, float x3, float y3);
    
    void update(float x1, float y1, float x2, float y2, float x3, float y3);
    
    Line& getSideA();
    
    Line& getSideB();
    
    Line& getSideC();
    
private:
    std::unique_ptr<Line> m_sideA;
    std::unique_ptr<Line> m_sideB;
    std::unique_ptr<Line> m_sideC;
};

#endif /* defined(__tappyplane__Triangle__) */