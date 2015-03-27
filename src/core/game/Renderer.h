//
//  Renderer.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/13/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__Renderer__
#define __tappyplane__Renderer__

#define WORLD_BACKGROUND_X SCREEN_WIDTH_1_2
#define WORLD_BACKGROUND_Y SCREEN_HEIGHT_1_2
#define WORLD_BACKGROUND_WIDTH SCREEN_WIDTH
#define WORLD_BACKGROUND_HEIGHT SCREEN_HEIGHT

#define TITLE_X SCREEN_WIDTH_1_2
#define TITLE_Y SCREEN_HEIGHT - 9
#define TITLE_WIDTH 11.7894737f
#define TITLE_HEIGHT 8

#define SCORE_FONT_X SCREEN_WIDTH_1_2
#define SCORE_FONT_Y SCREEN_HEIGHT / 4 * 3
#define SCORE_FONT_WIDTH 3.0f
#define SCORE_FONT_HEIGHT 4.17857142f

#define GAME_OVER_X SCREEN_WIDTH_1_2
#define GAME_OVER_Y SCREEN_HEIGHT - 7
#define GAME_OVER_WIDTH SCREEN_WIDTH / 8 * 7
#define GAME_OVER_HEIGHT 3.05825247f

#define DIALOG_GAME_OVER_X SCREEN_WIDTH_1_2
#define DIALOG_GAME_OVER_Y SCREEN_HEIGHT_1_2
#define DIALOG_GAME_OVER_WIDTH SCREEN_WIDTH_3_2 / 2
#define DIALOG_GAME_OVER_HEIGHT 10.4318181f

#define SCORE_FONT_IN_WINDOW_X 14.2f
#define SCORE_FONT_IN_WINDOW_Y 17.6f
#define BEST_FONT_IN_WINDOW_X 14.2f
#define BEST_FONT_IN_WINDOW_Y 12.6f
#define FONT_IN_WINDOW_WIDTH 1.43589744f
#define FONT_IN_WINDOW_HEIGHT 2.0f

#define MEDAL_X SCREEN_WIDTH_1_2 - 3.35f
#define MEDAL_Y SCREEN_HEIGHT_1_2 + 0.2f
#define MEDAL_WIDTH 4.4f
#define MEDAL_HEIGHT 4.59298247f

#include <memory>

class World;
class GameButton;
class Glove;
class Obstacle;
class SpriteBatcher;
class RectangleBatcher;
class LineBatcher;
class CircleBatcher;
class Font;
struct TextureWrapper;
class GameObject;
class TextureRegion;

class Renderer
{
public:
    Renderer();
    
    virtual void clearScreenWithColor(float r, float g, float b, float a) = 0;
    
    virtual void beginFrame() = 0;
    
    virtual void endFrame() = 0;
    
    virtual void cleanUp() = 0;
    
    void renderWorldBackground(World &world);
    
    void renderWorldForeground(World &world, Glove &glove, float titleAlpha);
    
    void renderWorldGameOver(World &world, GameButton &okButton, GameButton &leaderboardsButton, int bestScore);
    
protected:
    std::unique_ptr<SpriteBatcher> m_spriteBatcher;
    
    std::unique_ptr<TextureWrapper> m_backgroundTexture;
    std::unique_ptr<TextureWrapper> m_gameTexture;
    
private:
    std::unique_ptr<Font> m_font;
    
    void renderObstacle(Obstacle &obstacle);
    
    void renderGameObject(GameObject &go, TextureRegion tr);
};

#endif /* defined(__tappyplane__Renderer__) */