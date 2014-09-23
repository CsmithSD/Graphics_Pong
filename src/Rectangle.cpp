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


Rectangle::Rectangle( Point2D point, float width, float height, Color color, Velocity2D vel):
                      Entity2D( point, vel ), width(width), height(height), color(color)
{

}
Rectangle::~Rectangle()
{

}

void Rectangle::draw()
{
    glColor3f(color.r, color.g, color.b);
        glBegin( GL_LINE_LOOP );
        glVertex2f( point.x, point.y );
        glVertex2f( point.x+width, point.y );
        glVertex2f( point.x+width, point.y+width );
        glVertex2f( point.x, point.y+width );
    glEnd();
}

void Rectangle::translate2D( float x, float y )
{
    point.x += x;
    point.y += y;
}

void Rectangle::rotate2D( float yaw )
{
    point.yaw += yaw;
    while(point.yaw < 0 )
        point.yaw +=  ( M_PI * 2 );
    while( point.yaw >  ( M_PI * 2 ) )
        point.yaw -= ( M_PI * 2 );
}

void Rectangle::move2D( float x, float y, float yaw )
{
    point.x += x;
    point.y += y;
    point.yaw += yaw;
    while(point.yaw < 0 )
        point.yaw +=  ( M_PI * 2 );
    while( point.yaw >  ( M_PI *2  ) )
        point.yaw -= ( M_PI *2  );

}



Color Rectangle::get_color(){ return color; }

void Rectangle::set_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

void Rectangle::set_width(float width){ this->width = width;}
void Rectangle::set_height(float height){ this->height = height;}

void Rectangle::set_size(float width, float height)
{
    this->width = width;
    this->height = height;
}
