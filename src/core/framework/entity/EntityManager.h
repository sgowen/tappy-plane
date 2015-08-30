//
//  EntityManager.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/28/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__EntityManager__
#define __gowengamedev__EntityManager__

#define EntityMgr (EntityManager::getInstance())

#include <map>

class Entity;

typedef std::map<int, Entity*> EntityMap;

class EntityManager
{
public:
    static EntityManager* getInstance();
    
    Entity* getEntityFromID(int id)const;
    
    void registerEntity(Entity* entity);
    
    void removeEntity(Entity* entity);
    
    void reset();
    
private:
    EntityMap m_entityMap;
    
    EntityManager();
    
    //copy ctor and assignment should be private
    EntityManager(const EntityManager&);
    EntityManager& operator=(const EntityManager&);
};

#endif /* defined(__gowengamedev__EntityManager__) */
