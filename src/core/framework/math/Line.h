//
//  Line.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__Line__
#define __gowengamedev__Line__

#include <memory>

class Vector2D;

class Line
{
public:
    Line(float x1, float y1, float x2, float y2);
    
    Vector2D& getOrigin();
    
    Vector2D& getEnd();
    
private:
    std::unique_ptr<Vector2D> m_origin;
    std::unique_ptr<Vector2D> m_end;
};

#endif /* defined(__gowengamedev__Line__) */
