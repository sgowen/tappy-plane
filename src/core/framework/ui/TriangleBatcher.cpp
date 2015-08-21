//
//  TriangleBatcher.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 8/20/15.
//  Copyright (c) 2015 Techne Games. All rights reserved.
//

#include "TriangleBatcher.h"
#include "Triangle.h"
#include "Vector2D.h"

TriangleBatcher::TriangleBatcher(bool isFill)
{
    m_iNumTriangles = 0;
    m_isFill = isFill;
}

void TriangleBatcher::renderTriangle(Triangle &triangle, Color &color)
{
    renderTriangle(triangle.getPointA().getX(), triangle.getPointA().getY(), triangle.getPointB().getX(), triangle.getPointB().getY(), triangle.getPointC().getX(), triangle.getPointC().getY(), color);
}
