#ifndef _VELOCITY_2D_
#define _VELOCITY_2D_

struct Velocity2D
{
    Velocity2D(float x_vel = 0, float y_vel = 0, float yaw_vel = 0);
    float x_vel;
    float y_vel;
    float yaw_vel;
};

#endif