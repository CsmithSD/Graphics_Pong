#include "../include/Paddle.h"
#include <iostream>

Paddle::Paddle(Point2D point, float width, float height, Color color, Velocity2D vel ):
                FilledRectangle(point,width,height,color,vel)
{
    left_limit = 0;
    right_limit = 0;
    bottom_limit = 0;
    top_limit = 0;
}

Paddle::~Paddle()
{

}

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

void Paddle::set_limits(float left, float right, float bottom, float top)
{
    left_limit = left;
    right_limit = right;
    top_limit = top;
    bottom_limit = bottom;
}
