//
//  Assets.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/11/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "Assets.h"
#include "TextureRegion.h"
#include "PlaneDynamicGameObject.h"
#include "Glove.h"

Assets * Assets::getInstance()
{
	static Assets *assets = new Assets();
	return assets;
}

TextureRegion Assets::getWorldBackgroundTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(BACKGROUND_TEXTURE_REGION_X, BACKGROUND_TEXTURE_REGION_Y, BACKGROUND_TEXTURE_REGION_WIDTH, BACKGROUND_TEXTURE_REGION_HEIGHT, BACKGROUND_TEXTURE_WIDTH, BACKGROUND_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getTitleTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(TITLE_TEXTURE_REGION_X, TITLE_TEXTURE_REGION_Y, TITLE_TEXTURE_REGION_WIDTH, TITLE_TEXTURE_REGION_HEIGHT, BACKGROUND_TEXTURE_WIDTH, BACKGROUND_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getGloveTextureRegion(Glove &glove)
{
    static std::vector<TextureRegion> gloveTextureRegions;
	if(gloveTextureRegions.size() == 0)
	{
        gloveTextureRegions.push_back(TextureRegion(GLOVE_FRAME_1_TEXTURE_REGION_X, GLOVE_FRAME_1_TEXTURE_REGION_Y, GLOVE_FRAME_1_TEXTURE_REGION_WIDTH, GLOVE_FRAME_1_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
		gloveTextureRegions.push_back(TextureRegion(GLOVE_FRAME_2_TEXTURE_REGION_X, GLOVE_FRAME_2_TEXTURE_REGION_Y, GLOVE_FRAME_2_TEXTURE_REGION_WIDTH, GLOVE_FRAME_2_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
	}
    
	static float cycleTime = 0.80f;
	static std::vector<float> gloveFrames;
	if(gloveFrames.size() == 0)
	{
		gloveFrames.push_back(0.4f);
		gloveFrames.push_back(0.4f);
	}
    
    return gloveTextureRegions.at(getKeyFrameNumber(glove.getStateTime(), cycleTime, gloveFrames));
}

TextureRegion Assets::getTapLeftTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(TAP_LEFT_TEXTURE_REGION_X, TAP_LEFT_TEXTURE_REGION_Y, TAP_LEFT_TEXTURE_REGION_WIDTH, TAP_LEFT_TEXTURE_REGION_HEIGHT, BACKGROUND_TEXTURE_WIDTH, BACKGROUND_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getTapRightTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(TAP_RIGHT_TEXTURE_REGION_X, TAP_RIGHT_TEXTURE_REGION_Y, TAP_RIGHT_TEXTURE_REGION_WIDTH, TAP_RIGHT_TEXTURE_REGION_HEIGHT, BACKGROUND_TEXTURE_WIDTH, BACKGROUND_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getWorldForegroundLeftTextureRegion(Environment_Type type)
{
    static TextureRegion textureRegionGrass = TextureRegion(FOREGROUND_LEFT_TEXTURE_REGION_X, FOREGROUND_GRASS_LEFT_TEXTURE_REGION_Y, FOREGROUND_LEFT_TEXTURE_REGION_WIDTH, FOREGROUND_LEFT_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    
    static TextureRegion textureRegionRock = TextureRegion(FOREGROUND_LEFT_TEXTURE_REGION_X, FOREGROUND_ROCK_LEFT_TEXTURE_REGION_Y, FOREGROUND_LEFT_TEXTURE_REGION_WIDTH, FOREGROUND_LEFT_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    
    static TextureRegion textureRegionSnow = TextureRegion(FOREGROUND_LEFT_TEXTURE_REGION_X, FOREGROUND_SNOW_LEFT_TEXTURE_REGION_Y, FOREGROUND_LEFT_TEXTURE_REGION_WIDTH, FOREGROUND_LEFT_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    
    static TextureRegion textureRegionIce = TextureRegion(FOREGROUND_LEFT_TEXTURE_REGION_X, FOREGROUND_ICE_LEFT_TEXTURE_REGION_Y, FOREGROUND_LEFT_TEXTURE_REGION_WIDTH, FOREGROUND_LEFT_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    
    switch (type)
    {
        case GRASS:
            return textureRegionGrass;
        case ROCK:
            return textureRegionRock;
        case SNOW:
            return textureRegionSnow;
        case ICE:
        default:
            return textureRegionIce;
    }
}

TextureRegion Assets::getWorldForegroundRightTextureRegion(Environment_Type type)
{
    static TextureRegion textureRegionGrass = TextureRegion(FOREGROUND_RIGHT_TEXTURE_REGION_X, FOREGROUND_GRASS_RIGHT_TEXTURE_REGION_Y, FOREGROUND_RIGHT_TEXTURE_REGION_WIDTH, FOREGROUND_RIGHT_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    
    static TextureRegion textureRegionRock = TextureRegion(FOREGROUND_RIGHT_TEXTURE_REGION_X, FOREGROUND_ROCK_RIGHT_TEXTURE_REGION_Y, FOREGROUND_RIGHT_TEXTURE_REGION_WIDTH, FOREGROUND_RIGHT_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    
    static TextureRegion textureRegionSnow = TextureRegion(FOREGROUND_RIGHT_TEXTURE_REGION_X, FOREGROUND_SNOW_RIGHT_TEXTURE_REGION_Y, FOREGROUND_RIGHT_TEXTURE_REGION_WIDTH, FOREGROUND_RIGHT_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    
    static TextureRegion textureRegionIce = TextureRegion(FOREGROUND_RIGHT_TEXTURE_REGION_X, FOREGROUND_ICE_RIGHT_TEXTURE_REGION_Y, FOREGROUND_RIGHT_TEXTURE_REGION_WIDTH, FOREGROUND_RIGHT_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    
    switch (type)
    {
        case GRASS:
            return textureRegionGrass;
        case ROCK:
            return textureRegionRock;
        case SNOW:
            return textureRegionSnow;
        case ICE:
        default:
            return textureRegionIce;
    }
}

TextureRegion Assets::getWorldSpikeTextureRegion(Environment_Type type)
{
    static TextureRegion textureRegionGrass = TextureRegion(SPIKE_TEXTURE_REGION_X, SPIKE_GRASS_TEXTURE_REGION_Y, SPIKE_TEXTURE_REGION_WIDTH, SPIKE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    static TextureRegion textureRegionRock =  TextureRegion(SPIKE_TEXTURE_REGION_X,  SPIKE_ROCK_TEXTURE_REGION_Y, SPIKE_TEXTURE_REGION_WIDTH, SPIKE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    static TextureRegion textureRegionSnow =  TextureRegion(SPIKE_TEXTURE_REGION_X,  SPIKE_SNOW_TEXTURE_REGION_Y, SPIKE_TEXTURE_REGION_WIDTH, SPIKE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    static TextureRegion textureRegionIce =   TextureRegion(SPIKE_TEXTURE_REGION_X,   SPIKE_ICE_TEXTURE_REGION_Y, SPIKE_TEXTURE_REGION_WIDTH, SPIKE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    
    switch (type)
    {
        case GRASS:
            return textureRegionGrass;
        case ROCK:
            return textureRegionRock;
        case SNOW:
            return textureRegionSnow;
        case ICE:
        default:
            return textureRegionIce;
    }
}

TextureRegion Assets::getPlaneTextureRegion(PlaneDynamicGameObject &plane)
{
    static std::vector<TextureRegion> blueTextureRegions;
	if(blueTextureRegions.size() == 0)
	{
        blueTextureRegions.push_back(TextureRegion(PLANE_BLUE_FRAME_1_TEXTURE_REGION_X, PLANE_BLUE_FRAME_1_TEXTURE_REGION_Y, PLANE_TEXTURE_REGION_WIDTH, PLANE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
		blueTextureRegions.push_back(TextureRegion(PLANE_BLUE_FRAME_2_TEXTURE_REGION_X, PLANE_BLUE_FRAME_2_TEXTURE_REGION_Y, PLANE_TEXTURE_REGION_WIDTH, PLANE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
		blueTextureRegions.push_back(TextureRegion(PLANE_BLUE_FRAME_3_TEXTURE_REGION_X, PLANE_BLUE_FRAME_3_TEXTURE_REGION_Y, PLANE_TEXTURE_REGION_WIDTH, PLANE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
	}
    
    static std::vector<TextureRegion> greenTextureRegions;
	if(greenTextureRegions.size() == 0)
	{
        greenTextureRegions.push_back(TextureRegion(PLANE_GREEN_FRAME_1_TEXTURE_REGION_X, PLANE_GREEN_FRAME_1_TEXTURE_REGION_Y, PLANE_TEXTURE_REGION_WIDTH, PLANE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
		greenTextureRegions.push_back(TextureRegion(PLANE_GREEN_FRAME_2_TEXTURE_REGION_X, PLANE_GREEN_FRAME_2_TEXTURE_REGION_Y, PLANE_TEXTURE_REGION_WIDTH, PLANE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
		greenTextureRegions.push_back(TextureRegion(PLANE_GREEN_FRAME_3_TEXTURE_REGION_X, PLANE_GREEN_FRAME_3_TEXTURE_REGION_Y, PLANE_TEXTURE_REGION_WIDTH, PLANE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
	}
    
    static std::vector<TextureRegion> redTextureRegions;
	if(redTextureRegions.size() == 0)
	{
        redTextureRegions.push_back(TextureRegion(PLANE_RED_FRAME_1_TEXTURE_REGION_X, PLANE_RED_FRAME_1_TEXTURE_REGION_Y, PLANE_TEXTURE_REGION_WIDTH, PLANE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
		redTextureRegions.push_back(TextureRegion(PLANE_RED_FRAME_2_TEXTURE_REGION_X, PLANE_RED_FRAME_2_TEXTURE_REGION_Y, PLANE_TEXTURE_REGION_WIDTH, PLANE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
		redTextureRegions.push_back(TextureRegion(PLANE_RED_FRAME_3_TEXTURE_REGION_X, PLANE_RED_FRAME_3_TEXTURE_REGION_Y, PLANE_TEXTURE_REGION_WIDTH, PLANE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
	}
    
    static std::vector<TextureRegion> yellowTextureRegions;
	if(yellowTextureRegions.size() == 0)
	{
        yellowTextureRegions.push_back(TextureRegion(PLANE_YELLOW_FRAME_1_TEXTURE_REGION_X, PLANE_YELLOW_FRAME_1_TEXTURE_REGION_Y, PLANE_TEXTURE_REGION_WIDTH, PLANE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
		yellowTextureRegions.push_back(TextureRegion(PLANE_YELLOW_FRAME_2_TEXTURE_REGION_X, PLANE_YELLOW_FRAME_2_TEXTURE_REGION_Y, PLANE_TEXTURE_REGION_WIDTH, PLANE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
		yellowTextureRegions.push_back(TextureRegion(PLANE_YELLOW_FRAME_3_TEXTURE_REGION_X, PLANE_YELLOW_FRAME_3_TEXTURE_REGION_Y, PLANE_TEXTURE_REGION_WIDTH, PLANE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
	}
    
	static float cycleTime = 0.30f;
	static std::vector<float> planeFrames;
	if(planeFrames.size() == 0)
	{
		planeFrames.push_back(0.1f);
		planeFrames.push_back(0.1f);
		planeFrames.push_back(0.1f);
	}
    
    switch (plane.getType())
    {
        case BLUE:
            return blueTextureRegions.at(getKeyFrameNumber(plane.getStateTime(), cycleTime, planeFrames));
        case GREEN:
            return greenTextureRegions.at(getKeyFrameNumber(plane.getStateTime(), cycleTime, planeFrames));
        case RED:
            return redTextureRegions.at(getKeyFrameNumber(plane.getStateTime(), cycleTime, planeFrames));
        case YELLOW:
        default:
            return yellowTextureRegions.at(getKeyFrameNumber(plane.getStateTime(), cycleTime, planeFrames));
    }
}

TextureRegion Assets::getPuffLargeTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(PUFF_LARGE_TEXTURE_REGION_X, PUFF_LARGE_TEXTURE_REGION_Y, PUFF_LARGE_TEXTURE_REGION_WIDTH, PUFF_LARGE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getDialogTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(DIALOG_TEXTURE_REGION_X, DIALOG_TEXTURE_REGION_Y, DIALOG_TEXTURE_REGION_WIDTH, DIALOG_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getGameOverTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(GAME_OVER_TEXTURE_REGION_X, GAME_OVER_TEXTURE_REGION_Y, GAME_OVER_TEXTURE_REGION_WIDTH, GAME_OVER_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getOkButtonTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(OK_BUTTON_TEXTURE_REGION_X, OK_BUTTON_TEXTURE_REGION_Y, OK_BUTTON_TEXTURE_REGION_WIDTH, OK_BUTTON_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getLeaderboardsButtonTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(LEADERBOARDS_BUTTON_TEXTURE_REGION_X, LEADERBOARDS_BUTTON_TEXTURE_REGION_Y, LEADERBOARDS_BUTTON_TEXTURE_REGION_WIDTH, LEADERBOARDS_BUTTON_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getBronzeMedalTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(MEDAL_BRONZE_TEXTURE_REGION_X, MEDAL_TEXTURE_REGION_Y, MEDAL_TEXTURE_REGION_WIDTH, MEDAL_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getSilverMedalTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(MEDAL_SILVER_TEXTURE_REGION_X, MEDAL_TEXTURE_REGION_Y, MEDAL_TEXTURE_REGION_WIDTH, MEDAL_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getGoldMedalTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(MEDAL_GOLD_TEXTURE_REGION_X, MEDAL_TEXTURE_REGION_Y, MEDAL_TEXTURE_REGION_WIDTH, MEDAL_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

short Assets::getCurrentSoundId()
{
    return m_sCurrentSoundId;
}

void Assets::setCurrentSoundId(short soundId)
{
    m_sCurrentSoundId = soundId;
}

void Assets::resetCurrentSoundId()
{
    m_sCurrentSoundId = 0;
}

int Assets::getKeyFrameNumber(float stateTime, float cycleTime, std::vector<float> &frameDurations)
{
    if (stateTime > cycleTime && cycleTime > 0)
    {
        while(stateTime > cycleTime)
        {
            stateTime -= cycleTime;
        }
    }
    
    for (unsigned int i = 0; i < frameDurations.size(); i++)
    {
        if (stateTime < frameDurations.at(i))
        {
            return i;
        }
        
        stateTime -= frameDurations.at(i);
    }
    
    return 0;
}

Assets::Assets()
{
    // Hide Constructor for Singleton
}