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
    point.x += vel.x_vel * timestep;
    point.y += vel.y_vel * timestep;
    point.yaw += vel.yaw_vel * timestep;

    float x,y,rotated_x,rotated_y;
    //Precalculate sin and cos, 1/2 w and h
    float c = cos(point.yaw);
    float s = sin(point.yaw);
    float w = 0.5*width;
    float h = 0.5*height;
    
    //Bottom Left Corner
    x = - w;
    y = - h;
    rotated_x = x*c - y*s;
    rotated_y = x*s + y*c;
    if(  point.x+rotated_x < left_limit )
        point.x += left_limit - (rotated_x + point.x );
    else if(  point.x+rotated_x >= right_limit )
        point.x += right_limit - (rotated_x +  point.x );
    if(  point.y+rotated_y >= top_limit )
        point.y += top_limit - (rotated_y +  point.y );
    else if(  point.y+rotated_y <= bottom_limit )
        point.y += bottom_limit - (rotated_y +  point.y );
    //Top Left Corner
    //x = w; - don't need to recalculate
    y = h;
    rotated_x = x*c - y*s;
    rotated_y = x*s + y*c;
    if(  point.x+rotated_x <= left_limit )
        point.x += left_limit - (rotated_x +  point.x );
    else if(  point.x+rotated_x >= right_limit )
        point.x += right_limit - (rotated_x +  point.x );
    if(  point.y+rotated_y >= top_limit )
        point.y += top_limit - (rotated_y + point.y );
    else if(  point.y+rotated_y <= bottom_limit )
        point.y += bottom_limit - (rotated_y +  point.y );
    //Top Right Corner
    x = w;
    //y = point.y + h; - don't need to recalculate
    rotated_x = x*c - y*s;
    rotated_y = x*s + y*c;
    if(  point.x+rotated_x <= left_limit )
        point.x += left_limit - (rotated_x +  point.x );
    else if( x+rotated_x >= right_limit )
        point.x += right_limit - (rotated_x +  point.x );
    if(  point.y+rotated_y >= top_limit )
        point.y += top_limit - (rotated_y +  point.y );
    else if(  point.y+rotated_y <= bottom_limit )
        point.y += bottom_limit - (rotated_y +  point.y );
    //Bottom Right Corner
    //x = point.x + w; - don't need to recalculate
    y = - h;
    rotated_x = x*c - y*s;
    rotated_y = x*s + y*c;
    if( point.x+rotated_x <= left_limit )
        point.x += left_limit - (rotated_x +  point.x );
    else if(  point.x+rotated_x >= right_limit )
        point.x += right_limit - (rotated_x + point.x );
    if(  point.y+rotated_y >= top_limit )
        point.y += top_limit - (rotated_y + point.y );
    else if(  point.y+rotated_y <= bottom_limit )
        point.y += bottom_limit - (rotated_y +  point.y );
        
}

void Paddle::set_limits(float left, float right, float bottom, float top)
{
    left_limit = left;
    right_limit = right;
    top_limit = top;
    bottom_limit = bottom;
}
