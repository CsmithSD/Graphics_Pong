/******************************************************************************
* File: FilledCircle.h
* Authors: Ian Carlson, Christopher Smith
* Date: 09/16/14
* Last Modified 09/16/14
* Description: Header File for FilledCircle class\
* Inherits: Circle
* ****************************************************************************/



#ifndef _FILLED_CIRCLE_H_
#define _FILLED_CIRCLE_H_

#include "Circle.h"

class FilledCircle : public Circle
{
public:
    FilledCircle(Point2D point = Point2D(), float radius = 0, Color color = Color(1,1,1), Velocity2D vel = Velocity2D() );
    ~FilledCircle();

    void draw();
    void set_color(float r = 0, float g = 0, float b = 0);
    void set_outline_color(float r = 0, float g = 0, float b = 0);
    void set_fill_color(float r = 0, float g = 0, float b = 0);
    Color get_outline_color();
    Color get_fill_color();

private:
    //Contains the fill color
    Color color;
};

#endif
