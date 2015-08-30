//
//  State.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/28/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__State__
#define __gowengamedev__State__

template <class entity_type>
class State
{
public:
    virtual ~State()
    {
        // Empty
    }
    
    virtual void enter(entity_type*) = 0;
    
    virtual void execute(entity_type*) = 0;
    
    virtual void exit(entity_type*) = 0;
};

#endif /* defined(__gowengamedev__State__) */
