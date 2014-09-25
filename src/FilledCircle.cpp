#include "../include/FilledCircle.h"

FilledCircle::FilledCircle(Point2D point, float radius, Color color, Velocity2D vel):
        Circle(point, radius, color, vel), color(color)
{
    
}

FilledCircle::~FilledCircle()
{

}

void FilledCircle::draw()
{
    // specify the draw color
    glColor3f( color.r, color.g, color.b );
    int NumVert = 30;
    // draw an unfilled polygon
    float x = point.x;   // circle center
    float y = point.y;
    float r = radius;    // circle radius
    glBegin( GL_POLYGON );
    for ( int i = 0; i < NumVert; i++ )
    {
        glVertex2f( x + r * cos( 2 * M_PI * i / NumVert ), y + r * sin( 2 * M_PI * i / NumVert ) );
    }
    glEnd();

    Circle::draw();
}

void FilledCircle::set_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
    Circle::set_color(r,g,b);    
}

void FilledCircle::set_outline_color(float r, float g, float b)
{
    Circle::set_color(r,g,b);
}

void FilledCircle::set_fill_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

Color FilledCircle::get_outline_color()
{
    return Circle::get_color();
}

Color FilledCircle::get_fill_color()
{
    return color;
}

