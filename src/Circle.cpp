/******************************************************************************
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Source file for the Circle class.
 * Inherits: Entity.h
 * Inherited by:
 *****************************************************************************/

#include "../include/Circle.h"

Circle::Circle(float x, float y,float radius, Color color):
        Entity2D(x,y),radius(radius),color(color)
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
void Circle::set_radius( float radius){ this->radius = radius; }
