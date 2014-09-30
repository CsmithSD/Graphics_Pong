#include "../include/FilledRectangle.h"

FilledRectangle::FilledRectangle(Point2D point, float width, float height, Color color, Velocity2D vel): Rectangle(point,width,height,color,vel),color(color) 
{
    
}

FilledRectangle::~FilledRectangle()
{

}

void FilledRectangle::draw()
{    
    Point2D bl,br,tl,tr;
    get_corners(bl,br,tl,tr);
    glColor3f(color.r, color.g, color.b);
    
    glBegin( GL_POLYGON );
        glVertex2f(bl.x,bl.y);
        glVertex2f(tl.x,tl.y);
        glVertex2f(tr.x,tr.y);
        glVertex2f(br.x,br.y);
    glEnd();
    Rectangle::draw();
}

void FilledRectangle::set_color(float r, float g, float b)
{
    color.r = r;
    color.b = b;
    color.g = g;
    Rectangle::set_color(r,g,b);
}

void FilledRectangle::set_outline_color(float r, float g, float b)
{
    Rectangle::set_color(r,g,b);
}

void FilledRectangle::set_fill_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

Color FilledRectangle::get_fill_color()
{
    return color;
}

Color FilledRectangle::get_outline_color()
{
    return Rectangle::get_color();
}
