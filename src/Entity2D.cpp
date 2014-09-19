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
Entity2D::Entity2D( float x, float y, float yaw):
    x( x ), y( y ), yaw( yaw )
{

}

//Deconstructor
Entity2D::~Entity2D()
{

}

float Entity2D::get_x(){ return x; }
float Entity2D::get_y(){ return y; }
float Entity2D::get_yaw(){ return yaw; }

void Entity2D::set_x( float x ){ this->x = x; }
void Entity2D::set_y( float y ){ this->y = y; }
void Entity2D::set_yaw( float yaw ){ this->yaw = yaw; }

