#ifndef _POINT2D_H_
#define _POINT2D_H_


struct Point2D
{
    Point2D( float x = 0, float y = 0, float yaw = 0 ): x(x),y(y),yaw(yaw)
    {

    }
    float x;
    float y;
    float yaw;
};

#endif
