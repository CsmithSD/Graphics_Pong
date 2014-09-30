/******************************************************************************
* File: Paddle.h
* Authors: Ian Carlson, Christopher Smith
* Description: Source file for the Paddle class
* ****************************************************************************/
#include "../include/Paddle.h"

/******************************************************************************
* Function: Paddle( Point2D point, float width, float height, Color color, Velocity2D vel )
* Authors: Ian Carlson, Christopher Smith
* Description: Constructor for the Paddle Class
* Arguments:
*   point: Midpoint of the object
*   width: Width of the object
*   height: Height of the object
*   color: Color of the object
*   vel: velocity of the object
* ****************************************************************************/
Paddle::Paddle(Point2D point, float width, float height, Color color, Velocity2D vel ):
    FilledRectangle(point,width,height,color,vel)
{
    left_limit = 0;
    right_limit = 0;
    bottom_limit = 0;
    top_limit = 0;
}

/******************************************************************************
* Function: ~Paddle()
* Authors: Ian Carlson, Christopher Smith
* Description: Deconstructor for the Paddle Class
* ****************************************************************************/
Paddle::~Paddle()
{

}

/******************************************************************************
* Function: shrink()
* Authors: Ian Carlson, Christopher Smith
* Description: Shrinks the paddle by 10% every time it is hit by the ball
* ****************************************************************************/
void Paddle::shrink( )
{
    set_height( height *.9 );
    set_width(  width *  .9 );
}

/******************************************************************************
* Function: animate( float timestep )
* Authors: Ian Carlson, Christopher Smith
* Description: Moves the Paddle around the screen based on how long ago it
* was animated last and velocity
* Arguments:
*   timestep: time since the animate function was called last
* ****************************************************************************/
void Paddle::animate( float timestep )
{
    Point2D bl,br,tl,tr;
    translate2D(vel.x_vel*timestep,vel.y_vel*timestep);
    rotate2D(vel.yaw_vel*timestep);
    get_corners(bl,br,tl,tr);

    //Make sure bottom left corner is still in bounds
    if(  bl.x < left_limit )
        translate2D(left_limit - bl.x,0);
    else if(  bl.x >= right_limit )
        translate2D(right_limit - bl.x, 0);

    if(  bl.y >= top_limit )
        translate2D(0,top_limit - bl.y);
    else if( bl.y <= bottom_limit )
        translate2D(0,bottom_limit - bl.y);

    //get the updated corners, in case we moved
    get_corners(bl,br,tl,tr);

    //Make sure bottom right corner is still in bounds
    if(  br.x < left_limit )
        translate2D(left_limit - br.x,0);
    else if(  br.x >= right_limit )
        translate2D(right_limit - br.x, 0);

    if(  br.y >= top_limit )
        translate2D(0,top_limit - br.y);
    else if( br.y <= bottom_limit )
        translate2D(0,bottom_limit - br.y);

    //get the updated corners, in case we moved
    get_corners(bl,br,tl,tr);

    //Make sure top left corner is still in bounds
    if(  tl.x < left_limit )
        translate2D(left_limit - tl.x,0);
    else if(  tl.x >= right_limit )
        translate2D(right_limit - tl.x, 0);

    if(  tl.y >= top_limit )
        translate2D(0,top_limit - tl.y);
    else if( tl.y <= bottom_limit )
        translate2D(0,bottom_limit - tl.y);

    //get the updated corners, in case we moved
    get_corners(bl,br,tl,tr);

    //Make sure top right corner is still in bounds
    if(  tr.x < left_limit )
        translate2D(left_limit - tr.x,0);
    else if(  tr.x >= right_limit )
        translate2D(right_limit - tr.x, 0);

    if(  tr.y >= top_limit )
        translate2D(0,top_limit - tr.y);
    else if( tr.y <= bottom_limit )
        translate2D(0,bottom_limit - tr.y);

    //get the updated corners, in case we moved
    get_corners(bl,br,tl,tr);
}

/******************************************************************************
* Function: set_limits(float left, float right, float bottom, float top)
* Authors: Ian Carlson, Christopher Smith
* Description: Sets the bounds of the movable space for the paddle
* Arguments:
*   left: Left limit of the paddle
*   right: Right limit of the paddle
*   bottom: Bottom limit of the paddle
*   top:    Top limit of the paddle
* ****************************************************************************/
void Paddle::set_limits(float left, float right, float bottom, float top)
{
    left_limit = left;
    right_limit = right;
    top_limit = top;
    bottom_limit = bottom;
}
