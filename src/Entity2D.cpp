/******************************************************************************
* File: Entity.cpp
* Authors: Ian Carlson, Christopher Smith
* Date: 09/16/14
* Last Modified 09/16/14
* Description: Source file for the Entity class, the parent of all
* drawable objects for our programs.
* ****************************************************************************/

#include "../include/Entity.h"


//Constructor
Entity2D::Entity2D( float x = 0, float y = 0, float yaw = 0 ):
    x( x ), y( y ), yaw( yaw )
{

}

//Deconstructor
Entity2D::~Entity2D()
{

}

float Entity2D::get_x(){ return x; }
float Entity::get_y(){ return y; }
float Entity::get_yaw(){ return yaw; }

void Entity2D::set_x( float x ){ this.x = x; }
void Entity2D::set_y( float y ){ this.y = y; }
void Entity2D::set_yaw( float yaw ){ this.yaw = yaw; }

void Entity2D::translate2D(float x, float y)
{

}

void Entity2D::rotate2D( float yaw )
{

}

void Entity2D::move2D( float x, float y, float yaw )
{
    translate2D(x, y);
    rotate2D(yaw);
}