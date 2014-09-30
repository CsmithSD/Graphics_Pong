/******************************************************************************
* File: Entity.cpp
* Authors: Ian Carlson, Christopher Smith
* Date: 09/16/14
* Last Modified 09/16/14
* Description: Source file for the Entity class, the parent of all
* drawable objects for our programs.
* ****************************************************************************/

#include "../include/Entity2D.h"
//Constructor
Entity2D::Entity2D( Point2D point, Velocity2D vel ):point(point), vel(vel)
{
}

//Destructor
Entity2D::~Entity2D()
{
}

float Entity2D::get_x() {
    return point.x;
}
float Entity2D::get_y() {
    return point.y;
}
float Entity2D::get_yaw() {
    return point.yaw;
}
Point2D Entity2D::get_point() {
    return point;
}
Velocity2D Entity2D::get_velocity() {
    return vel;
}
void Entity2D::set_velocity(float x, float y, float yaw)
{
    vel.x_vel = x;
    vel.y_vel = y;
    vel.yaw_vel = yaw;
}
