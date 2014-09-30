/******************************************************************************
* File: Entity.cpp
* Authors: Ian Carlson, Christopher Smith
* Date: 09/16/14
* Last Modified 09/16/14
* Description: Source file for the Entity class, the parent of all
* drawable objects for our programs.
* ****************************************************************************/

#include "../include/Entity2D.h"

/******************************************************************************
* Function: Entity2D( Point2D point, Velocity2D vel )
* Authors: Ian Carlson, Christopher Smith
* Description: Constructor for the Entity2D object
* Arguments:
*   point: Midpoint of the object
*   vel: velocity of the object
* ****************************************************************************/
Entity2D::Entity2D( Point2D point, Velocity2D vel ):point(point), vel(vel)
{
}


/******************************************************************************
* Function: ~Entity2D
* Authors: Ian Carlson, Christopher Smith
* Description: Deconstructor for the Entity2D object
* ****************************************************************************/
Entity2D::~Entity2D()
{
}

/******************************************************************************
* Function: get_x()
* Authors: Ian Carlson, Christopher Smith
* Description: Returns the x coordinate of the midpoint
* ****************************************************************************/
float Entity2D::get_x() {
    return point.x;
}
/******************************************************************************
* Function: get_y()
* Authors: Ian Carlson, Christopher Smith
* Description: Returns the y coordinate of the midpoint
* ****************************************************************************/
float Entity2D::get_y() {
        return point.y;
}
/******************************************************************************
* Function: get_yaw()
* Authors: Ian Carlson, Christopher Smith
* Description: Returns the orientation of the midpoint (object)
* ****************************************************************************/
float Entity2D::get_yaw() {
    return point.yaw;
}
/******************************************************************************
* Function: get_point()
* Authors: Ian Carlson, Christopher Smith
* Description: Returns the coordinates of the midpoint in a Point2D object
* ****************************************************************************/
Point2D Entity2D::get_point() {
    return point;
}
/******************************************************************************
* Function: get_velocity()
* Authors: Ian Carlson, Christopher Smith
* Description: Returns the velocity of the object
* ****************************************************************************/
Velocity2D Entity2D::get_velocity() {
    return vel;
}
/******************************************************************************
* Function: set_velocity( float x, float y, float yaw )
* Authors: Ian Carlson, Christopher Smith
* Description: Sets the velocity of the object to new a new x,y, and yaw directions
* Arguments:
*   x: new x velocity of the object
*   y: new y velocity of the object
* ****************************************************************************/
void Entity2D::set_velocity(float x, float y, float yaw)
{
    vel.x_vel = x;
    vel.y_vel = y;
    vel.yaw_vel = yaw;
}
