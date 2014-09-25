#include "../include/Paddle.h"

Paddle::Paddle(Point2D point, float width, float height, Color color, Velocity2D vel ):
                FilledRectangle(point,width,height,color,vel)
{

}

Paddle::~Paddle()
{

}

void Paddle::animate( float timestep )
{

}


