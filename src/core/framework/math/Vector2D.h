//
//  Vector2D.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef Vector2D_H
#define Vector2D_H

class Vector2D
{
public:
    Vector2D(float x = 0, float y = 0) : m_fX(x), m_fY(y) {}
    
    Vector2D(const Vector2D &cSource);
    
    Vector2D set(const Vector2D &other);
    Vector2D set(float x, float y);
	Vector2D setX(float x);
	Vector2D setY(float y);

	Vector2D cpy();
    
    void operator+= (const Vector2D &other);
    Vector2D add(float x, float y);
    
    void operator-= (const Vector2D &other);
    Vector2D sub(float x, float y);
    
    Vector2D operator*= (float scalar);
    Vector2D mul(float scalar);
    
    float len();
    
    Vector2D nor();
    
    float angle();
    
    Vector2D rotate(float angle);
    
    float dist(const Vector2D &other) const;
    float dist(float x, float y) const;
    
    float distSquared(const Vector2D &other) const;
    float distSquared(float x, float y) const;
    
    float getX() const;
    float getY() const;
    
private:
    float m_fX;
    float m_fY;
};

#endif /* Vector2D_H */
