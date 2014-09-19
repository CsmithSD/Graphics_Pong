
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

class Entity2D
{
    public:
    //Virtual Functions
    virtual void draw() = 0;

    //Functions
    Entity2D(float x = 0, float y = 0, float yaw = 0);
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
    virtual void translate2D(float x, float y);
    virtual void rotate2D(float yaw);
    virtual void move2D(float x, float y, float yaw);

    private:

    //Variables
    public:
    
    protected:
    float x;
    float y;
    float yaw;
};

#endif
