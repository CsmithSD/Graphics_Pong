/******************************************************************************
 * File: Rectangle.h
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/30/14
 * Description: Header file for the Rectangle class.
 * Inherits: Entity2D.h
 * Inherited by: FilledRectangle
 * ***************************************************************************/

#ifndef _RECTANGLE_H_
#define RECTANGLE_H_
#include <math.h>
#include <GL/freeglut.h>
#include "Color.h"
#include "Entity2D.h"
#include "Velocity2D.h"
#include "Point2D.h"

class Rectangle : public Entity2D
{
public:
    Rectangle(Point2D point = Point2D(), float width = 0, float height = 0,  Color color = Color(1,1,1), Velocity2D vel = Velocity2D());
    ~Rectangle();

    //Implemented virtual functions
    void draw();
    void translate2D( float x, float y);
    void rotate2D( float yaw);
    void move2D( float x, float y, float yaw = 0 );

    void set_color(float r = 1, float g = 1, float b = 1);
    void set_width(float width);
    void set_height(float height);
    void set_size(float width, float height);
    float get_width();
    float get_height();
    Color get_color();
    void get_corners(Point2D & bl, Point2D & br, Point2D & tl, Point2D & tr);
protected:
    //Width/Height & outline color of Rectangle
    float width;
    float height;
    Color color;

private:
    //Corner points so they don't get recalculated multiple times
    void update_corners();
    Point2D bl_corner;
    Point2D br_corner;
    Point2D tr_corner;
    Point2D tl_corner;
};
#endif
