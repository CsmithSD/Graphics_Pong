/******************************************************************************
* File: FilledCircle.cpp
* Authors: Ian Carlson, Christopher Smith
* Date: 9/16/14
* Date Modified: 9/30/14
* Description: Source File for the FilledCircle Class
* ****************************************************************************/
#include "../include/FilledCircle.h"

/******************************************************************************
* Function: FilledCircle(Point2D point, float radius, Color color, Velocity2D vel)
* Authors: Ian Carlson, Christopher Smith
* Description: Constructor for the Filled Circle class
* Arguments:
*   point: Midpoint of the object
*   radius: Radius of the circle
*   color: Outline and Filled Color of the circle
*   vel: velocity of the object
* ****************************************************************************/
FilledCircle::FilledCircle(Point2D point, float radius, Color color, Velocity2D vel):
    Circle(point, radius, color, vel), color(color)
{

}

/******************************************************************************
* Function: ~FilledCircle()
* Authors: Ian Carlson, Christopher Smith
* Description: Deconstructor for the Entity2D object
* ****************************************************************************/
FilledCircle::~FilledCircle()
{

}

/******************************************************************************
* Function: draw()
* Authors: Ian Carlson, Christopher Smith
* Description: Draws the filled circle to the screen
* ****************************************************************************/
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
    //Calls the Parent draw function for the outline of the circle incase of multi colored
    Circle::draw();
}

/******************************************************************************
* Function: set_color( float r, float g, float b)
* Authors: Ian Carlson, Christopher Smith
* Description: sets both the outline and fill color to an rgb color
* Arguments:
*    r: Red color to be set
*    b: Blue color to be set
*    g: green color to be set
******************************************************************************/
void FilledCircle::set_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
    Circle::set_color(r,g,b);
}

/******************************************************************************
* Function: set_outline_color( float r, float g, float b)
* Authors: Ian Carlson, Christopher Smith
* Description: sets the outline color to an rgb color
* Arguments:
*    r: Red color to be set
*    b: Blue color to be set
*    g: green color to be set
******************************************************************************/
void FilledCircle::set_outline_color(float r, float g, float b)
{
    Circle::set_color(r,g,b);
}

/******************************************************************************
* Function: set_fill_color( float r, float g, float b)
* Authors: Ian Carlson, Christopher Smith
* Description: setsthe fill color to an rgb color
* Arguments:
*    r: Red color to be set
*    b: Blue color to be set
*    g: green color to be set
******************************************************************************/
void FilledCircle::set_fill_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

/******************************************************************************
* Function: get_outline_color()
* Authors: Ian Carlson, Christopher Smith
* Description: Returns the outline color of the circle
* ****************************************************************************/
Color FilledCircle::get_outline_color()
{
    return Circle::get_color();
}

/******************************************************************************
* Function: get_fill_color()
* Authors: Ian Carlson, Christopher Smith
* Description: returns the fill color of the circle
* ****************************************************************************/
Color FilledCircle::get_fill_color()
{
    return color;
}

