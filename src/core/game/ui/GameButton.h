//
//  GameButton.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__GameButton__
#define __tappyplane__GameButton__

#include "PhysicalEntity.h"

class GameButton : public PhysicalEntity
{
public:
    GameButton(float x, float y, float width, float height);
};

#endif /* defined(__tappyplane__GameButton__) */