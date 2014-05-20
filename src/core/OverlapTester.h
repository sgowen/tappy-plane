//
//  OverlapTester.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/11/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __tappyplane__OverlapTester__
#define __tappyplane__OverlapTester__

class Vector2D;
class Rectangle;
class Triangle;
class Line;

class OverlapTester
{
public:
    static bool doRectanglesOverlap(Rectangle &r1, Rectangle &r2);
    
	static bool isPointInRectangle(const Vector2D &p, Rectangle &r);
    
    static bool doesRectangleOverlapTriangle(Rectangle &r, Triangle &t);
    
    static bool doLineAndRectangleOverlap(Line &l, Rectangle &r);

private:
    static bool doLinesIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
    
    // Hide the Constructor
    OverlapTester();
};

#endif /* defined(__tappyplane__OverlapTester__) */