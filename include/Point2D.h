/******************************************************************************
* File: Point2D.h
* Authors: Ian Carlson, Christopher Smith
* Date: 09/16/14
* Last Modified 09/16/14
* Description: Header file of a struct that contains the center point and orientation
* of a point
* ****************************************************************************/


#ifndef _POINT2D_H_
#define _POINT2D_H_


struct Point2D
{
    Point2D( float x = 0, float y = 0, float yaw = 0 ): x(x),y(y),yaw(yaw)
    {

    }
    float x;
    float y;
    float yaw;
};

#endif
