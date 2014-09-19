/******************************************************************************
* File: Rectangle.h
* Authors: Ian Carlson, Christopher Smith
* Date: 09/16/14
* Last Modified: 09/16/14
* Description: Source File for the Rectangle class.
* Inherits: Entity2D.h
* Inherited by:
* ***************************************************************************/
#include "../include/Rectangle.h"


Rectangle::Rectangle( float width, float height, float x, float y, Color color ):
                      Entity2D( x, y ), width(width), height(height), color(color)
{

}
Rectangle::~Rectangle()
{

}

void Rectangle::draw()
{
    glColor3f(color.r, color.g, color.b);
        glBegin( GL_LINE_LOOP );
        glVertex2f( x, y );
        glVertex2f( x+width, y );
        glVertex2f( x+width, y+width );
        glVertex2f( x, y+width );
    glEnd();
}

Color Rectangle::get_color(){ return color; }

void Rectangle::set_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

void Rectangle::set_width(float width){ this.width = width;}
void Rectangle::set_height(float height){ this.height = height;}

void Rectangle::set_size(float width, float height)
{
    this.width = width;
    this.height = height;
}
