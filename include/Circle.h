/******************************************************************************
 * File: Circle.h
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Header file for the Circle class.
 * Inherits: Entity.h
 * Inherited by: 
 * ***************************************************************************/

#include "Entity.h"

class Circle
{
    Circle(float radius, float x, float y);
    ~Circle();
    void draw();
    

    private:
    float radius;
};
