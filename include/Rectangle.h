/******************************************************************************
 * File: Rectangle.h
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Header file for the Rectangle class.
 * Inherits: Entity2D.h
 * Inherited by: 
 * ***************************************************************************/

#ifndef _RECTANGLE_H_
#define RECTANGLE_H_

#include "Color.h"
#include "Entity2D.h"

class Rectangle : public Entity2D.h
{
    Rectangle(float width = 0, float height = 0, float x = 0, float y = 0);
    ~Rectangle();
    
    void draw();
    void set_color(float r = 0; float g = 0; float b = 0);
    void set_width(float width);
    void set_height(float height);
    void set_size(float width, float height);

    private:
    float width;
    float height;
    Color color;
};
#endif
