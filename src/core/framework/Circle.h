//
//  Circle.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/6/13.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__Circle__
#define __gowengamedev__Circle__

#include <memory>

class Vector2D;

class Circle
{
public:
	float m_fRadius;

    Circle(float x, float y, float radius);
    
	Vector2D& getCenter() const;

private:
	std::unique_ptr<Vector2D> m_center;
};

#endif /* defined(__gowengamedev__Circle__) */