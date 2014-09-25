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

void Ball::animate(float timestamp)
{

}

void Ball::set_limits(float left, float right, float bottom, float top)
{
    left_limit = left;
    right_limit = right;
    top_limit = top;
    bottom_limit = bottom;
}
