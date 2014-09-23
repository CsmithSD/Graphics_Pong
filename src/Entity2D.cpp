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

//Deconstructor
Entity2D::~Entity2D()
{

}

float Entity2D::get_x(){ return point.x; }
float Entity2D::get_y(){ return point.y; }
float Entity2D::get_yaw(){ return point.yaw; }

void Entity2D::set_x( float x ){ this->point.x = x; }
void Entity2D::set_y( float y ){ this->point.y = y; }
void Entity2D::set_yaw( float yaw ){ this->point.yaw = yaw; }

