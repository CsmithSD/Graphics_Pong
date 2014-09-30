/******************************************************************************
 * File: Color.h
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Simple struct definition for handling colors.
 * ***************************************************************************/

#ifndef _COLOR_H_
#define _COLOR_H_
struct Color
{
    Color(float r = 1, float g = 1, float b = 1);
    float r;
    float g;
    float b;
};

#endif
