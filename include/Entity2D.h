
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
#include "Point.h"
class Entity2D
{
    public:
    //Virtual Functions
    virtual void draw() = 0;

    //Functions
    Entity2D(Point2D point = Point2D( ), Velocity2D vel = Velocity2D() );
    ~Entity2D();

    //Getters
    float get_x();
    float get_y();
    float get_yaw();

    //Setters
    void set_x(float x);
    void set_y(float y);
    void set_yaw(float yaw);

    //Movement
    virtual void translate2D(float x, float y) = 0;
    virtual void rotate2D(float yaw) = 0;
    virtual void move2D(float x, float y, float yaw) = 0;
    virtual void animate(float timestep ) = 0;
    private:

    //Variables
    public:
    
    protected:
    Point2D point;
    float yaw;
    float x_vel;
    float y_vel;
    float yaw_vel;
};

#endif
