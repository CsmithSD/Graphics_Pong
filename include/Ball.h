#ifndef _BALL_H_
#define _Ball_H_

#include "FilledCircle.h"

class Ball:public FilledCircle
{
    public:
        Ball(Point2D point = Point2D(), float radius = 0, Color color = Color(1,1,1), Velocity2D vel = Velocity2D() );
        ~Ball();

        void animate(float timestamp);

    private:
};

#endif
