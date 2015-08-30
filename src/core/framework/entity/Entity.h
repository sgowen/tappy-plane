//
//  Entity.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/3/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__Entity__
#define __gowengamedev__Entity__

class Entity
{
public:
    Entity();
    
    virtual void update(float deltaTime);
    
    int getID();
    
    float getStateTime();
    
protected:
    float m_fStateTime;
    
private:
    static int getUniqueEntityID();
    
    int m_ID;
};

#endif /* defined(__gowengamedev__Entity__) */
