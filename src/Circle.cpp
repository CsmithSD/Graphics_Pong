/******************************************************************************
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Source file for the Circle class.
 * Inherits: Entity.h
 * Inherited by:
 *****************************************************************************/

#include "../include/Circle.h"

Circle::Circle(Point2D p, float radius, Color color, Velocity2D vel)
        Entity2D(p, vel), radius(radus), color(color)
{

}

Circle::~Circle(){}

void Circle::draw()
{

}

void Circle::translate2D(float x, float y)
{
    set_x(get_x()+x);
    set_y(get_y()+y);
}

void Circle::rotate2D( float yaw )
{
    float new_yaw = get_yaw() + yaw;
    while(new_yaw > 2 * M_PI)
        new_yaw -= 2 * M_PI;
    while(new_yaw < 0 )
        new_yaw += 2 * M_PI;
    set_yaw(new_yaw);
}

void Circle::move2D( float x, float y, float yaw)
{
    translate2D(x,y);
    rotate2D(yaw);
}


void Circle::set_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

float Circle::get_radius(){ return radius; }
void Circle::set_radius( float radius){ this->radius = radius; }
