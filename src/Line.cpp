#include "../include/Line.h"

Line::Line(Point p1, Point p2, Color color ): p1(p1), p2(p2), color(color){}

void Line::draw()
{

}

void Line::set_color(float r, float g, float b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

void Line::set_p1( Point p1 )
{
    this -> p1 = p1;
}

void Line::set_p2( Point p2 )
{
    this -> p2 = p2;
}

void Line::get_p1()
{
    return p1;
}

void Line::get_p2()
{
    return p2;
}

void Line::translate2D( float x, float y )
{
    p1.x += x;
    p2.x += x;
    
    p1.y += y;
    p2.y += y;
}

void Line::rotate2D( float yaw )
{
    this -> yaw += yaw;
    while(this -> yaw < 0 )
        yaw +=  ( M_PI << 1 );
    while( this -> yaw >  ( M_PI << 1 ) )
        yaw -= ( M_PI << 1 )
}

void Line::move2D( float x, float y, float yaw );
{
    p1.x += x;
    p2.x += x;
    
    p1.y += y;
    p2.y += y;

    this -> yaw += yaw;
    while(this -> yaw < 0 )
        yaw +=  ( M_PI << 1 );
    while( this -> yaw >  ( M_PI << 1 ) )
        yaw -= ( M_PI << 1 )

}

void Line::translate2Dp1(float x, float y)
{
    p1.x += x;
    p1.y += y;
}

void Line::translate2Dp2(float x, float y)
{
    p2.x += x;
    p2.y += y;
}

void Line::move2Dp1( float x, float y, float yaw)
{
    p1.x += x;
    p1.y += y;
    this -> yaw += yaw;
    while(this -> yaw < 0 )
        yaw +=  ( M_PI << 1 );
    while( this -> yaw >  ( M_PI << 1 ) )
        yaw -= ( M_PI << 1 )

}

void Line::move2Dp2( float x, floaty, float yaw)
{
    p2.x += x;
    p2.y += y;
    this -> yaw += yaw;
    while(this -> yaw < 0 )
        yaw +=  ( M_PI << 1 );
    while( this -> yaw >  ( M_PI << 1 ) )
        yaw -= ( M_PI << 1 )

}