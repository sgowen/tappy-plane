//
//  Rectangle.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef Rectangle_H
#define Rectangle_H

#include <memory>

class Vector2D;

class Rectangle
{
public:
    Rectangle(float x, float y, float width, float height, float angle = 0);
    
    Vector2D& getLowerLeft();
    
    const float getWidth() const;
    
    const void setWidth(float width);
    
    const float getHeight() const;
    
    const void setHeight(float height);
    
    const float getAngle() const;
    
    const void setAngle(float angle);
    
private:
    std::unique_ptr<Vector2D> m_LowerLeft;
    float m_fWidth;
    float m_fHeight;
    float m_fAngle;
};

#endif /* Rectangle_H */
