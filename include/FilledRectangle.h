#ifndef _FILLED_RECTANGLE_H_
#define _FILLED_RECTANGLE_H_

#include "Rectangle.h"

class FilledRectangle : public Rectangle
{
public:
    FilledRectangle(Point2D point = Point2D(), float width = 0, float height = 0, Color color = Color(1,1,1),Velocity2D vel = Velocity2D());
    ~FilledRectangle();

    void draw();
    void set_color(float r = 0, float g = 0, float b = 0);
    void set_outline_color(float r = 0, float g = 0, float b = 0);
    void set_fill_color(float r = 0, float g = 0, float b = 0);
    Color get_outline_color();
    Color get_fill_color();

private:
    Color color;
};

#endif
