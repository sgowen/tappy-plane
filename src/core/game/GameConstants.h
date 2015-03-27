//
//  GameConstants.h
//  tappyplane
//
//  Created by Stephen Gowen on 5/13/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#define SCREEN_WIDTH 18
#define SCREEN_WIDTH_7_8 15.75f
#define SCREEN_WIDTH_6_8 13.50f
#define SCREEN_WIDTH_5_8 11.25f
#define SCREEN_WIDTH_1_2 9
#define SCREEN_WIDTH_3_8 6.75f
#define SCREEN_WIDTH_2_8 4.50f
#define SCREEN_WIDTH_1_8 2.25f
#define SCREEN_WIDTH_3_2 27
#define SCREEN_HEIGHT 32
#define SCREEN_HEIGHT_1_2 16

// Game World Definitions
#define GAME_WORLD_BASE 3.20792079f
#define GAME_WORLD_BASE_1_2 GAME_WORLD_BASE / 2
#define GAME_RESET_OBSTACLE_X SCREEN_WIDTH / 8 * 15
#define GAME_OFF_SCREEN_OBSTACLE_X -SCREEN_WIDTH / 8 * 15

#define GAME_X 0.80f
#define GAME_Y 0.60f

#define GRID_CELL_SIZE 1.43283582f

#define GRID_CELL_WIDTH GRID_CELL_SIZE
#define GRID_CELL_HEIGHT GRID_CELL_SIZE

#define GRID_CELL_NUM_ROWS 17
#define NUM_GRID_CELLS_PER_ROW 15

#endif /* GAME_CONSTANTS_H */
