#include "../include/Ball.h"


Ball::Ball(Point2D point, float radius, Color color, Velocity2D vel ):
    FilledCircle(point,radius,color,vel)
{

}

Ball::~Ball()
{

}

void Ball::animate(float timestamp)
{

}
