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
    float x,y,rotated_x,rotated_y;
    //Precalculate sin and cos, 1/2 w and h
    float c = cos(point.yaw);
    float s = sin(point.yaw);
    float w = 0.5*width;
    float h = 0.5*height;
    glColor3f(color.r, color.g, color.b);
        glBegin( GL_LINE_LOOP );

        //Bottom Left Corner
        x = - w;
        y = - h;
        rotated_x = x*c - y*s;
        rotated_y = x*s + y*c;
        glVertex2f( point.x + rotated_x, point.y + rotated_y );

        //Top Left Corner
        //x = point.x-w; - don't need to recalculate
        y = h;
        rotated_x = x*c - y*s;
        rotated_y = x*s + y*c;
        glVertex2f( point.x + rotated_x, point.y + rotated_y );

        //Top Right Corner
        x = w;
        //y = point.y + h; - don't need to recalculate
        rotated_x = x*c - y*s;
        rotated_y = x*s + y*c;
        glVertex2f( point.x + rotated_x, point.y + rotated_y );

        //Bottom Right Corner
        //x = point.x + w; - don't need to recalculate
        y = - h;
        rotated_x = x*c - y*s;
        rotated_y = x*s + y*c;
        glVertex2f( point.x + rotated_x, point.y + rotated_y );
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
    point.x = x;
    point.y = y;
    point.yaw = yaw;
}

Color Rectangle::get_color(){ return color; }

void Rectangle::set_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

float Rectangle::get_width(){ return width; }
float Rectangle::get_height(){ return height; }

void Rectangle::set_width(float width){ this->width = width;}
void Rectangle::set_height(float height){ this->height = height;}

void Rectangle::set_size(float width, float height)
{
    this->width = width;
    this->height = height;
}
