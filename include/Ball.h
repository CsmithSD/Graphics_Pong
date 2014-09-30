/******************************************************************************
* File: Ball.h
* Authors: Ian Carlson, Christopher Smith
* Date: 09/25/14
* Last Modified 09/30/14
* Description: Header file for the ball class with class definition
* Inherits: FilledCircle class.
* ****************************************************************************/


#ifndef _BALL_H_
#define _Ball_H_

#include "FilledCircle.h"
//included since an argument to the check_paddle_collision function is of type Paddle
#include "Paddle.h"
class Ball:public FilledCircle
{
public:
    Ball(Point2D point = Point2D(), float radius = 0, Color color = Color(1,1,1), Velocity2D vel = Velocity2D() );
    ~Ball();

    void animate(float timestep);
    int goal_made();
    void set_limits(float left, float right, float bottom, float top);
    bool check_paddle_collision( Paddle& paddle, float ball_scale_factor, float paddle_scale_factor );
private:

    //Limits of the field of play
    float left_limit;
    float right_limit;
    float bottom_limit;
    float top_limit;
    float calc_distance( Point2D p1, Point2D p2 );
    //variable that holds the values 0 (no goal), 1 (Right player scored), 2 (Left player scored)
    int goal;
};




#endif
