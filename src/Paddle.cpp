#include "../include/Paddle.h"

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

}

void Paddle::set_limits(float left, float right, float bottom, float top)
{
    left_limit = left;
    right_limit = right;
    top_limit = top;
    bottom_limit = bottom;
}
