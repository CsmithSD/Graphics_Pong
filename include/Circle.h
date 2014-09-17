/******************************************************************************
 * File: Circle.h
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Header file for the Circle class.
 * Inherits: Entity2D.h
 * Inherited by: 
 * ***************************************************************************/
#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Color.h"
#include "Entity2D.h"

class Circle : public Entity2D
{
    Circle(float radius = 0, float x = 0, float y = 0);
    ~Circle();
    void draw();
    void set_color(float r = 0, float g = 0, float b = 0);
    float get_radius();
    void set_radius(float radius);

    protected:
    float radius;

    private:
    Color color;
};

#endif
