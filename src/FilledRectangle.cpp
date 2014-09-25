#include "../include/FilledRectangle.h"

FilledRectangle::FilledRectangle(Point2D point, float width, float height, Color color, Velocity2D vel): Rectangle(point,width,height,color,vel),color(color) 
{
    
}

FilledRectangle::~FilledRectangle()
{

}

void FilledRectangle::draw()
{
    float x,y,rotated_x,rotated_y;
    //Precalculate sin and cos, 1/2 w and h
    float c = cos(point.yaw);
    float s = sin(point.yaw);
    float w = 0.5*width;
    float h = 0.5*height;
    glColor3f(color.r, color.g, color.b);
        glBegin( GL_POLYGON );

        //Bottom Left Corner
        x = - w;
        y = - h;
        rotated_x = x*c - y*s;
        rotated_y = x*s + y*c;
        glVertex2f( point.x + rotated_x, point.y + rotated_y );

        //Top Left Corner
        //x = w; - don't need to recalculate
        y = h;
        rotated_x = x*c - y*s;
        rotated_y = x*s + y*c;
        glVertex2f( point.x + rotated_x, point.y + rotated_y );

        //Top Right Corner
        x = w;
        //y = point.y + h; - don't need to recalculate
        rotated_x = x*c - y*s;
        rotated_y = x*s + y*c;
        glVertex2f( point.x + rotated_x, point.y +rotated_y );

        //Bottom Right Corner
        //x = point.x + w; - don't need to recalculate
        y = - h;
        rotated_x = x*c - y*s;
        rotated_y = x*s + y*c;
        glVertex2f( point.x + rotated_x, point.y + rotated_y );
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
