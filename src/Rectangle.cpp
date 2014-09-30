/******************************************************************************
* File: Rectangle.h
* Authors: Ian Carlson, Christopher Smith
* Date: 09/16/14
* Last Modified: 09/16/14
* Description: Source File for the Rectangle class. The rectangle class
* is an abstract class the maintains it's own four corners and line color and
* supplies a draw function.
* ***************************************************************************/
#include "../include/Rectangle.h"


/******************************************************************************
* Function: Rectange(Point2D point, float width, float height, Color color,
*                    Velocity2D vel)
* Authors: Ian Carlson, Christopher Smith
* Description: Constructor for the Rectangle class.
* Arguments:
*   point: center of the rectangle
*   width: width of the rectangle
*   height: height of the rectangle
*   color: color for the outline of the rectangle
*   vel: Starting velocity of the ball
* ****************************************************************************/
Rectangle::Rectangle( Point2D point, float width, float height, Color color, Velocity2D vel):
    Entity2D( point, vel ), width(width), height(height), color(color)
{
    update_corners();
}


/******************************************************************************
* Function: ~Rectange()
* Authors: Ian Carlson, Christopher Smith
* Description: Desstructor for the Rectangle class.
* ****************************************************************************/
Rectangle::~Rectangle()
{

}

/******************************************************************************
* Function: get_corners(Point2D &bl, Point2D &br, Point2D &tl, Point2D & tr)
* Authors: Ian Carlson, Christopher Smith
* Description: Returns a copy of the four corners of the rectangle
* Arguments:
*   bl: bottom left corner
*   br: bottom right corner
*   tl: top left corner
*   tr: top right corner
* ****************************************************************************/
void Rectangle::get_corners(Point2D & bl, Point2D & br, Point2D & tl, Point2D & tr)
{
    bl = bl_corner;
    br = br_corner;
    tl = tl_corner;
    tr = tr_corner;
}

/******************************************************************************
* Function: update_corners()
* Authors: Ian Carlson, Christopher Smith
* Description: Given the height, width, yaw, and center position of
*   the rectangle, update the corner locations to respond to translations
*   or rotations.
* ****************************************************************************/
void Rectangle::update_corners()
{
    float x, y, rotated_x, rotated_y;

    //precalculate all the trig functions for efficiency
    float c = cos(point.yaw);
    float s = sin(point.yaw);

    //distance of the corners from the center assuming no rotation
    float w = 0.5*width;
    float h = 0.5*height;

    //bottom left corner
    x = - w; //offset from rectangle center
    y = - h;
    rotated_x = x*c - y*s; //rotate the offset
    rotated_y = x*s + y*c;
    bl_corner.x = rotated_x + point.x; //add the rotated offset
    bl_corner.y = rotated_y + point.y; //to the center point

    //Top Left Corner
    //x = point.x-w; - don't need to recalculate
    y = h;
    rotated_x = x*c - y*s;
    rotated_y = x*s + y*c;
    tl_corner.x = rotated_x + point.x;
    tl_corner.y = rotated_y + point.y;

    //Top Right Corner
    x = w;
    //y = point.y + h; - don't need to recalculate
    rotated_x = x*c - y*s;
    rotated_y = x*s + y*c;
    tr_corner.x = rotated_x + point.x;
    tr_corner.y = rotated_y + point.y;

    //Bottom Right Corner
    //x = point.x + w; - don't need to recalculate
    y = - h;
    rotated_x = x*c - y*s;
    rotated_y = x*s + y*c;
    br_corner.x = rotated_x + point.x;
    br_corner.y = rotated_y + point.y;
}

/******************************************************************************
* Function: draw()
* Authors: Ian Carlson, Christopher Smith
* Description: draw the rectangle as a line loop
* ****************************************************************************/
void Rectangle::draw()
{
    Point2D bl,br,tl,tr;
    get_corners(bl,br,tl,tr);
    glColor3f(color.r, color.g, color.b);
    glBegin( GL_LINE_LOOP );
    glVertex2f(bl.x,bl.y);
    glVertex2f(tl.x,tl.y);
    glVertex2f(tr.x,tr.y);
    glVertex2f(br.x,br.y);
    glEnd();
}

/******************************************************************************
* Function: translate2D(float x, float y)
* Authors: Ian Carlson, Christopher Smith
* Description: translates the rectangle
* Arguments:
*   x: translation left or right
*   y: translation up or down
* Note: These are GL coordinate, not screen coordinates
* ****************************************************************************/
void Rectangle::translate2D( float x, float y )
{
    point.x += x;
    point.y += y;
    update_corners();
}

/******************************************************************************
* Function: rotate2D(float yaw)
* Authors: Ian Carlson, Christopher Smith
* Description: rotate the rectangle
* Arguments:
*   yaw: the angle by which to rotate the rectangle
* ****************************************************************************/
void Rectangle::rotate2D( float yaw )
{
    point.yaw += yaw;
    while(point.yaw < 0 )
        point.yaw +=  ( M_PI * 2 );
    while( point.yaw >  ( M_PI * 2 ) )
        point.yaw -= ( M_PI * 2 );
    update_corners();
}

/******************************************************************************
* Function: move2D(float yaw)
* Authors: Ian Carlson, Christopher Smith
* Description: set the rectangle to a specified position and rotation
* Arguments:
*   x: new horizontal position
*   y: new vertical position
*   yaw: new rotation
* Note: The coordinates are GL coordinates, not screen coordinates
* ****************************************************************************/
void Rectangle::move2D( float x, float y, float yaw )
{
    point.x = x;
    point.y = y;
    point.yaw = yaw;
    update_corners();
}

/******************************************************************************
* Function: get_color()
* Authors: Ian Carlson, Christopher Smith
* Description: return the color of the rectangle outline
* ****************************************************************************/
Color Rectangle::get_color()
{
    return color;
}

/******************************************************************************
* Function: set_color(float r, float g, float b)
* Authors: Ian Carlson, Christopher Smith
* Description: set the color of the rectangle outline
* Arguments:
*   r: red color component
*   g: green color component
*   b: blue color component
* Note: Arguments are floating point numbers [0,1]
* ****************************************************************************/
void Rectangle::set_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

/******************************************************************************
* Function: get_width()
* Authors: Ian Carlson, Christopher Smith
* Description: return the width of the rectangle
* ****************************************************************************/
float Rectangle::get_width()
{
    return width;
}

/******************************************************************************
* Function: get_height()
* Authors: Ian Carlson, Christopher Smith
* Description: return the height of the rectangle
* ****************************************************************************/
float Rectangle::get_height()
{
    return height;
}

/******************************************************************************
* Function: set_width(float width)
* Authors: Ian Carlson, Christopher Smith
* Description: set the width of the rectangle
* Arguments:
*   width: the new width of the rectangle
* ****************************************************************************/
void Rectangle::set_width(float width)
{
    this->width = width;
    update_corners();
}

/******************************************************************************
* Function: set_height(float height)
* Authors: Ian Carlson, Christopher Smith
* Description: set the height of the rectangle
* Arguments:
*   width: the new height of the rectangle
* ****************************************************************************/
void Rectangle::set_height(float height)
{
    this->height = height;
    update_corners();
}

/******************************************************************************
* Function: set_size(float width, float height)
* Authors: Ian Carlson, Christopher Smith
* Description: set the width and height of the rectangle
* Arguments:
*   width: the new width of the rectangle
*   height: the new height of the rectangle
* ****************************************************************************/
void Rectangle::set_size(float width, float height)
{
    this->width = width;
    this->height = height;
    update_corners();
}
