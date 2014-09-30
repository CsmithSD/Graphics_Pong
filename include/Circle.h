/******************************************************************************
 * File: Circle.h
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Header file for the Circle class with class definition
 * Inherits: Entity2D.h
 * Inherited by: FilledCircle
 * ***************************************************************************/
#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <math.h>
#include "Color.h"
#include "Entity2D.h"
#include <GL/freeglut.h>
class Circle : public Entity2D
{
public:
    Circle(Point2D point = Point2D(), float radius = 0, Color color = Color(1,1,1), Velocity2D velocity = Velocity2D() );
    ~Circle();
    //Implemnted virtual functions
    void draw();
    void translate2D(float x, float y);
    void rotate2D(float yaw);
    void move2D( float x, float y, float yaw = 0 );

    Color get_color();
    void set_color(float r = 1, float g = 1, float b = 1);
    float get_radius();
    void set_radius(float radius);

protected:
    float radius;
    Color color;
};

#endif
