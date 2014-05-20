//
//  Rectangle.h
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef Rectangle_H
#define Rectangle_H

class Vector2D;

class Rectangle
{
public:
    Rectangle(float x, float y, float width, float height, float angle = 0);
    
    ~Rectangle();
    
    Vector2D& getLowerLeft();
    
    const float getWidth() const;
    
    const void setWidth(float width);
    
    const float getHeight() const;
    
    const void setHeight(float height);
    
    const float getAngle() const;
    
    const void setAngle(float angle);
    
private:
    Vector2D *m_LowerLeft;
    float m_fWidth;
    float m_fHeight;
    float m_fAngle;
};

#endif /* Rectangle_H */