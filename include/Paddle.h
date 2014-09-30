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
    float left_limit;
    float right_limit;
    float top_limit;
    float bottom_limit;
};

#endif
