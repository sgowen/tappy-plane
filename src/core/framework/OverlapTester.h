//
//  OverlapTester.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__OverlapTester__
#define __gowengamedev__OverlapTester__

class Vector2D;
class Circle;
class Rectangle;
class Triangle;
class Line;

class OverlapTester
{
public:
    static bool doCirclesOverlap(const Circle &c1, const Circle &c2);
    
    static bool doRectanglesOverlap(Rectangle &r1, Rectangle &r2);
    
    static bool doesRectangleOverlapTriangle(Rectangle &r, Triangle &t);
    
    static bool overlapCircleRectangle(const Circle &c, Rectangle &r);
    
    static bool isPointInRectangle(const Vector2D &p, Rectangle &r);
    
    static bool isPointInCircle(const Vector2D &p, const Circle &c);
    
    static bool isPointInTriangle(Vector2D &p, Triangle &t);
    
    static bool doLineAndRectangleOverlap(Line &l, Rectangle &r);

private:
    /* A utility function to calculate area of triangle formed by (x1, y1), (x2, y2) and (x3, y3) */
    static float calcArea(float x1, float y1, float x2, float y2, float x3, float y3);
    static bool doLinesIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
    
    // Hide the Constructor
    OverlapTester();
};

#endif /* defined(__gowengamedev__OverlapTester__) */
