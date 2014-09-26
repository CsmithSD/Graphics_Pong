#include "../include/Ball.h"


Ball::Ball(Point2D point, float radius, Color color, Velocity2D vel ):
    FilledCircle(point,radius,color,vel)
{
    left_limit = 0;
    right_limit = 0;
    top_limit = 0;
    bottom_limit = 0;
}

Ball::~Ball()
{

}

void Ball::animate(float timestep)
{
    point.x += vel.x_vel * timestep;
    point.y += vel.y_vel * timestep;
    point.yaw += vel.yaw_vel * timestep;

    if( point.x <= left_limit )
    {
        vel.x_vel *= -1;
        point.x += left_limit - point.x;
    }
    else if( point.x >= right_limit )
    {
        vel.x_vel *= -1;
        point.x += right_limit - point.x;
    }
    if( point.y <= bottom_limit )
    {
        vel.y_vel *= -1;
        point.y += bottom_limit - point.y;
    }
    else if( point.y >= top_limit )
    {
        vel.y_vel *= -1;
        point.y += top_limit - point.y;
    }
}

void Ball::set_limits(float left, float right, float bottom, float top)
{
    left_limit = left;
    right_limit = right;
    top_limit = top;
    bottom_limit = bottom;
}
