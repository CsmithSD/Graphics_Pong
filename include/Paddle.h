/******************************************************************************
* File: Paddle.h
* Authors: Ian Carlson, Christopher Smith
* Date: 09/16/14
* Last Modified 09/30/14
* Description: Header file for the Paddle Class
* Inherits: FilledRectangle
* ****************************************************************************/

#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "FilledRectangle.h"

class Paddle:public FilledRectangle
{
public:
    Paddle( Point2D point = Point2D(), float width = 0, float height = 0, Color color = Color(1,1,1),Velocity2D vel = Velocity2D() );
    ~Paddle();

    void shrink();
    void animate(float timestep);
    void set_limits(float left, float right, float bottom, float top);
private:
    //Limits for the Paddle to stay on its side of the playing field
    float left_limit;
    float right_limit;
    float top_limit;
    float bottom_limit;
};

#endif
