//
//  GridGameObject.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 5/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "GridGameObject.h"
#include "Vector2D.h"
#include "Rectangle.h"
#include "GameConstants.h"

GridGameObject::GridGameObject(int gridX, int gridY, float width, float height, float angle) : GameObject(GAME_X + GRID_CELL_WIDTH * gridX + GRID_CELL_WIDTH / 2.0f, GAME_Y + GRID_CELL_HEIGHT * gridY + GRID_CELL_HEIGHT / 2.0f, width, height, angle)
{
    m_gridX = gridX;
    m_gridY = gridY;
}

int GridGameObject::getGridX()
{
    return m_gridX;
}

int GridGameObject::getGridY()
{
    return m_gridY;
}