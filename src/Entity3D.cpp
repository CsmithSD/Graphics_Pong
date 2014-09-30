/******************************************************************************
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified 09/16/14
 * Description: Source file for the Entity3D class, the parent of all
 * 3D drawable objects for our programs.
 * ****************************************************************************/


#include "../include/Entity3D.h"

Entity3D::Entity3D( float x, float y, float z,
                    float roll, float pitch, float yaw ):
    Entity2D( x, y, yaw ), z(z), roll(roll), pitch(pitch)
{

}

Entity3D::~Entity3D()
{

}

float Entity3D::get_z() {
    return z;
}
float Entity3D::get_roll() {
    return roll;
}
float Entity3D::get_pitch() {
    return pitch;
}

void Entity3D::set_z( float z ) {
    this.z = z;
}
void Entity3D::set_roll(float roll) {
    this.roll = roll
}
void Entity3D::set_pitch( float pitch ) {
    this.pitch = pitch
}
Entity3D::translate3D(float x, float y, float z)
{

}

void Entity3D::rotate3D( float roll, float pitch, float yaw )
{

}

void Entitdy3D::move3D( float x, float y, float z, float roll, float pitch, float yaw )
{
    translate3D( x , y , z );
    rotate3D( roll, pitch, yaw );
}
