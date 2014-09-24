/******************************************************************************
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Source file for the Circle class.
 * Inherits: Entity.h
 * Inherited by:
 *****************************************************************************/

#include "../include/Circle.h"

Circle::Circle(Point2D point, float radius, Color color, Velocity2D vel):
         Entity2D(point, vel), radius(radius), color(color)
{

}

Circle::~Circle(){}

void Circle::draw()
{
    
    // clear the display using the "clear" color (black)
    glClear( GL_COLOR_BUFFER_BIT );

    // specify the draw color
    glColor3f( color.r, color.g, color.b );
    int NumVert = 20;
    // draw an unfilled polygon
    float x = point.x;   // circle center
    float y = point.y;
    float r = radius;    // circle radius
    glBegin( GL_LINE_LOOP );
    for ( int i = 0; i < NumVert; i++ )
    {
        glVertex2f( x + r * cos( 2 * M_PI * i / NumVert ), y + r * sin( 2 * M_PI * i / NumVert ) );
    }
    glEnd();

    // flush graphical output to the display
    glFlush();
}

void Circle::translate2D(float x, float y)
{
    point.x += x;
    point.y += y;
}

void Circle::rotate2D( float yaw )
{
    point.yaw += yaw;
    while(point.yaw > 2 * M_PI)
        point.yaw -= 2 * M_PI;
    while(point.yaw < 0 )
        point.yaw += 2 * M_PI;
}

void Circle::move2D( float x, float y, float yaw)
{
    point.x = x;
    point.y = y;
    point.yaw = yaw;
}


void Circle::set_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

Color Circle::get_color()
{
    return color;
}

float Circle::get_radius(){ return radius; }
void Circle::set_radius( float radius){ this->radius = radius; }
