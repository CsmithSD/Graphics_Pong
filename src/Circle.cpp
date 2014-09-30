/******************************************************************************
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Source file for the Circle class.
 * Inherits: Entity.h
 * Inherited by:
 *****************************************************************************/

#include "../include/Circle.h"
/******************************************************************************
* Function: Circle( Point2D point, float radius, Color color, Velocity2D vel)
* Authors: Ian Carlson, Christopher Smith
* Description: Constructor for the circle object
* Arguments:
*   point: center point of the circle
*   radius: radius of the circle
*   color: outline color of the circle
*   vel: velocity of the circle
* ****************************************************************************/

Circle::Circle(Point2D point, float radius, Color color, Velocity2D vel):
    Entity2D(point, vel), radius(radius), color(color)
{

}
/******************************************************************************
* Function: ~Circle()
* Authors: Ian Carlson, Christopher Smith
* Description: Deconstructor for the circle class
* ****************************************************************************/

Circle::~Circle() {}


/******************************************************************************
* Function: draw()
* Authors: Ian Carlson, Christopher Smith
* Description: Draws the circle on the screen
* ****************************************************************************/
void Circle::draw()
{
    // specify the draw color
    glColor3f( color.r, color.g, color.b );
    int NumVert = 30;
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
}


/******************************************************************************
* Function: Translate2D( float x, float y)
* Authors: Ian Carlson, Christopher Smith
* Date: 09/16/14
* Last Modified 09/16/14
* Description: Increments the center point of the circle  by and x and y offset
* Arguments:
*   x: midpoint increment to increase the x coordinate by
*   y: midpoint increment to increase the y coordinate by
* ****************************************************************************/
void Circle::translate2D(float x, float y)
{
    point.x += x;
    point.y += y;
}

/******************************************************************************
* Function: rotate2D( float yaw )
* Authors: Ian Carlson, Christopher Smith
* Date: 09/16/14
* Last Modified 09/16/14
* Description: Sets the rotation of hte circle between 0 and 2*PI
* Arguments:
*   yaw: Rotation in radians to increase yaw by
* ****************************************************************************/
void Circle::rotate2D( float yaw )
{
    point.yaw += yaw;
    while(point.yaw > 2 * M_PI)
        point.yaw -= 2 * M_PI;
    while(point.yaw < 0 )
        point.yaw += 2 * M_PI;
}

/******************************************************************************
* Function: move2D( float x, float y, float yaw)
* Authors: Ian Carlson, Christopher Smith
* Description: Moves the circle in absolute position without adding onto the
* coordinates
* Arguments:
*   x: New x position
*   y: New y position
* yaw: New orientation
* ****************************************************************************/
void Circle::move2D( float x, float y, float yaw)
{
    point.x = x;
    point.y = y;
    point.yaw = yaw;
}

/******************************************************************************
* Function set_color( float r, float g, float b)
* Authors: Ian Carlson, Christopher Smith
* Description: Sets the rgb values of the outline of the circle
* Argument:
*   r: red value of the color
*   g: green value of the color
*   b: blue value of the color
* ****************************************************************************/
void Circle::set_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

/******************************************************************************
* Function: get_color()
* Authors: Ian Carlson, Christopher Smith
* Description: Returns the color in a struct to the caller
* ****************************************************************************/
Color Circle::get_color()
{
    return color;
}

/******************************************************************************
* Function: get_radius()
* Authors: Ian Carlson, Christopher Smith
* Description: Returns the radius to the caller
* ****************************************************************************/
float Circle::get_radius() {
    return radius;
}

/******************************************************************************
* Function: set_radius( float radius )
* Authors: Ian Carlson, Christopher Smith
* Description: Sets the radius of the circle
*   radius: New radius to set the circle to
* ****************************************************************************/
void Circle::set_radius( float radius) {
    this->radius = radius;
}
