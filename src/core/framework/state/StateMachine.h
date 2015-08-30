//
//  StateMachine.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/28/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__StateMachine__
#define __gowengamedev__StateMachine__

#include <cassert>

#include "State.h"

template <class entity_type>
class StateMachine
{
public:
    
    StateMachine(entity_type* owner) : m_owner(owner), m_currentState(NULL), m_previousState(NULL), m_globalState(NULL)
    {
        // Empty
    }
    
    virtual ~StateMachine()
    {
        // Empty
    }
    
    void setCurrentState(State<entity_type>* state)
    {
        m_currentState = state;
    }
    
    void setGlobalState(State<entity_type>* state)
    {
        m_globalState = state;
    }
    
    void setPreviousState(State<entity_type>* state)
    {
        m_previousState = state;
    }
    
    void execute()const
    {
        if (m_globalState)
        {
            m_globalState->execute(m_owner);
        }
        
        if (m_currentState)
        {
            m_currentState->execute(m_owner);
        }
    }
    
    void changeState(State<entity_type>* newState)
    {
        assert(newState && "<StateMachine::ChangeState>:trying to assign null state to current");
        
        m_previousState = m_currentState;
        
        m_currentState->exit(m_owner);
        
        m_currentState = newState;
        
        m_currentState->enter(m_owner);
    }
    
    void revertToPreviousState()
    {
        changeState(m_previousState);
    }
    
    bool isInState(const State<entity_type>& st)const
    {
        return typeid (*m_currentState) == typeid (st);
    }
    
    State<entity_type>* getCurrentState() const
    {
        return m_currentState;
    }
    
    State<entity_type>* getGlobalState() const
    {
        return m_globalState;
    }
    
    State<entity_type>* getPreviousState() const
    {
        return m_previousState;
    }
    
private:
    entity_type* m_owner;
    
    State<entity_type>* m_currentState;
    State<entity_type>* m_previousState;
    State<entity_type>* m_globalState;
};

#endif /* defined(__gowengamedev__StateMachine__) */
