/******************************************************************************
* File: FilledRectangle.cpp
* Authors: Ian Carlson, Christopher Smith
* Date: 9/16/14
* Date Modified: 9/30/14
* Description: Source file for the FilledRectangle Class
* ****************************************************************************/
#include "../include/FilledRectangle.h"

/******************************************************************************
* Function: FilledRectangle( Point2D piont, float width, float height, Color color, velocity2D vel)
* Authors: Ian Carlson, Christopher Smith
* Description: Constructor for the FilledRectangle object
* Arguments:
    point: Midpoint of the object
    width: Width of the rectangle
    height: Height of the recangle
    color: Fill and outline color of the rectangle
    vel: velocity of the object
* ****************************************************************************/
FilledRectangle::FilledRectangle(Point2D point, float width, float height, Color color, Velocity2D vel): Rectangle(point,width,height,color,vel),color(color)
{

}

/******************************************************************************
* Function: ~FilledRectangle
* Authors: Ian Carlson, Christopher Smith
* Description: Deonstructor for the Entity2D object
* ****************************************************************************/
FilledRectangle::~FilledRectangle()
{

}

/******************************************************************************
* Function: draw()
* Authors: Ian Carlson, Christopher Smith
* Description: Draws the FilledRectangle on the screen
* ****************************************************************************/
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
    //Calls the parent draw since it could have a different outline color
    Rectangle::draw();
}

/******************************************************************************
* Function: set_color( float r, float g, float b )
* Authors: Ian Carlson, Christopher Smith
* Description: Sets the color of both the fill and outline portions
* Arguments:
*   r: Red color to be used to set the colors
*   b: Blue color to be used to set the colors
*   g: Green color to be used to set the colors
* ****************************************************************************/
void FilledRectangle::set_color(float r, float g, float b)
{
    color.r = r;
    color.b = b;
    color.g = g;
    Rectangle::set_color(r,g,b);
}

/******************************************************************************
* Function: set_outline_color(float r, floag g, float b)
* Authors: Ian Carlson, Christopher Smith
* Description: Sets the outline color of the rectangle
* Arguments:
    r: Red color to be used to set the outline color
    b: Blue color to be used to set the outline color
    g: Green color to be used to set the outline color
* ****************************************************************************/
void FilledRectangle::set_outline_color(float r, float g, float b)
{
    Rectangle::set_color(r,g,b);
}

/******************************************************************************
* Function: set_fill_color( float r, float g, float b)
* Authors: Ian Carlson, Christopher Smith
* Description: sets fill color of the rectangle
* Arguments:
*   r: Red color to be used to set the fill color
*   b: Blue color to be used to set the fill color
*   g: Green color to be used to set the fill color
* ****************************************************************************/
void FilledRectangle::set_fill_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

/******************************************************************************
* Function: get_fill_color()
* Authors: Ian Carlson, Christopher Smith
* Description: Returns the fill color in a Color object to the caller
* ****************************************************************************/
Color FilledRectangle::get_fill_color()
{
    return color;
}

/******************************************************************************
* Function: get_outline_color()
* Authors: Ian Carlson, Christopher Smith
* Description: Returns the outline color in a Color object to the caller
* ****************************************************************************/
Color FilledRectangle::get_outline_color()
{
    return Rectangle::get_color();
}
