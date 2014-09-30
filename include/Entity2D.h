
/******************************************************************************
 * File: Entity2D.h
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Header file for the Entity2D class, the parent of all
 * drawable objects for our programs.
 * ***************************************************************************/

#ifndef _ENTITY_2D_
#define _ENTITY_2D_
#include "Point2D.h"
#include "Velocity2D.h"
#include <math.h>
class Entity2D
{
public:
    //Virtual Functions
    virtual void draw() = 0;

    //Functions
    Entity2D(Point2D point = Point2D(), Velocity2D vel = Velocity2D() );
    ~Entity2D();

    //Getters
    float get_x();
    float get_y();
    float get_yaw();
    Point2D get_point();
    Velocity2D get_velocity();
    //setter
    void set_velocity(float x, float y, float yaw = 0);
    //virtual movement functions
    virtual void translate2D(float x, float y) = 0;
    virtual void rotate2D(float yaw) = 0;
    virtual void move2D(float x, float y, float yaw) = 0;
    virtual void animate(float timestep ) = 0;

protected:
    //contains the center point of all entity objects
    Point2D point;
    //contains the velocity of all entity objects
    Velocity2D vel;
};

#endif
