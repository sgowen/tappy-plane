//
//  Triangle.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    m_sideA = std::unique_ptr<Line>(new Line(x1, y1, x2, y2));
    m_sideB = std::unique_ptr<Line>(new Line(x2, y2, x3, y3));
    m_sideC = std::unique_ptr<Line>(new Line(x3, y3, x1, y1));
}

void Triangle::set(float x1, float y1, float x2, float y2, float x3, float y3)
{
    m_sideA->getOrigin().set(x1, y1);
    m_sideA->getEnd().set(x2, y2);
    m_sideB->getOrigin().set(x2, y2);
    m_sideB->getEnd().set(x3, y3);
    m_sideC->getOrigin().set(x3, y3);
    m_sideC->getEnd().set(x1, y1);
}

Vector2D& Triangle::getPointA()
{
    return m_sideA->getOrigin();
}

Vector2D& Triangle::getPointB()
{
    return m_sideB->getOrigin();
}

Vector2D& Triangle::getPointC()
{
    return m_sideC->getOrigin();
}

Line& Triangle::getSideA()
{
    return *m_sideA;
}

Line& Triangle::getSideB()
{
    return *m_sideB;
}

Line& Triangle::getSideC()
{
    return *m_sideC;
}
