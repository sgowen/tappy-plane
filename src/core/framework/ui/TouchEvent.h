//
//  TouchEvent.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef TouchEvent_H
#define TouchEvent_H

typedef enum
{
    DOWN,
    DRAGGED,
    UP
} Touch_Type;

class TouchEvent
{
private:
    Touch_Type m_type;
    float m_fX;
    float m_fY;
    
public:
    TouchEvent(float x, float y, Touch_Type type);

	Touch_Type getTouchType();

	void setTouchType(Touch_Type touchType);

	float getX();

	void setX(float x);

	float getY();

	void setY(float y);
};

#endif /* TouchEvent_H */