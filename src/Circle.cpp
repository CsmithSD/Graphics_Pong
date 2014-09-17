/******************************************************************************
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Source file for the Circle class.
 * Inherits: Entity.h
 * Inherited by:
 *****************************************************************************/

#include "../include/Circle.h"

Circle::Circle(float radius, float x, float y): radius(radius), x(x), y(y),
                                                color.r(1),color.g(1),color.b(1)
{

}

Circle::~Circle(){}

void Circle::draw()
{

}

void Circle::set_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

float Circle::get_radius(){ return radius; }
void Circle::set_radius( float radius){ this.radius = radius; }
