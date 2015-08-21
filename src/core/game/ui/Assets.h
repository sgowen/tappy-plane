//
//  Assets.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__Assets__
#define __tappyplane__Assets__

#define MAX_SOUNDS_TO_PLAY_PER_FRAME 3

#include <vector>
#include "EnvironmentType.h"

class TextureRegion;
class PlanePhysicalEntity;
class Glove;

class Assets
{
public:
    static Assets * getInstance();
    
    static TextureRegion& getWorldBackgroundTextureRegion();
    
    static TextureRegion& getTitleTextureRegion();
    
    static TextureRegion& getGloveTextureRegion(Glove &glove);
    
    static TextureRegion& getTapLeftTextureRegion();
    
    static TextureRegion& getTapRightTextureRegion();
    
    static TextureRegion& getWorldForegroundLeftTextureRegion(Environment_Type type);
    
    static TextureRegion& getWorldForegroundRightTextureRegion(Environment_Type type);
    
    static TextureRegion& getWorldSpikeTextureRegion(Environment_Type type);
    
    static TextureRegion& getPlaneTextureRegion(PlanePhysicalEntity &plane);
    
    static TextureRegion& getPuffLargeTextureRegion();
    
    static TextureRegion& getDialogTextureRegion();
    
    static TextureRegion& getGameOverTextureRegion();
    
    static TextureRegion& getOkButtonTextureRegion();
    
    static TextureRegion& getLeaderboardsButtonTextureRegion();
    
    static TextureRegion& getBronzeMedalTextureRegion();
    
    static TextureRegion& getSilverMedalTextureRegion();
    
    static TextureRegion& getGoldMedalTextureRegion();
    
    short getFirstSoundId();
    
    void addSoundIdToPlayQueue(short soundId);
    
    void eraseFirstSoundId();

private:
    Assets();
    
    static int getKeyFrameNumber(float stateTime, float cycleTime, std::vector<float> &frameDurations);
    
    std::vector<short> m_sSoundIds;
};

#endif /* defined(__tappyplane__Assets__) */