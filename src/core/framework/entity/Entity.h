//
//  Entity.h
//  nosfuratu
//
//  Created by Stephen Gowen on 8/3/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __nosfuratu__Entity__
#define __nosfuratu__Entity__

struct Telegram;

class Entity
{
public:
    Entity();
    
    virtual void update(float deltaTime);
    
    virtual bool handleMessage(const Telegram& msg) = 0;
    
    int getID();
    
    float getStateTime();
    
protected:
    float m_fStateTime;
    
private:
    static int getUniqueEntityID();
    
    int m_ID;
};

#endif /* defined(__nosfuratu__Entity__) */
