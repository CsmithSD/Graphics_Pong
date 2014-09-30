#ifndef _BALL_H_
#define _Ball_H_

#include "FilledCircle.h"
#include "Paddle.h"
class Ball:public FilledCircle
{
    public:
        Ball(Point2D point = Point2D(), float radius = 0, Color color = Color(1,1,1), Velocity2D vel = Velocity2D() );
        ~Ball();

    void animate(float timestep);
    void set_limits(float left, float right, float bottom, float top);
    void check_paddle_collision( Paddle& paddle, float scale_factor );
    private:
    float left_limit;
    float right_limit;
    float bottom_limit;
    float top_limit;
    float calc_distance( Point2D p1, Point2D p2 );
};




#endif
