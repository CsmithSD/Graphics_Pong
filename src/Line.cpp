#include "../include/Line.h"

Line::Line(Point2D p1, Point2D p2, Color color, Velocity2D vel )
    : Entity2D(Point2D(), vel), p1(p1), p2(p2), color(color)
{
    calculate_midpoint();
}

void Line::calculate_midpoint()
{
    set_x( (p1.x + p2.x)/2.0);
    set_y( (p1.y + p2.y)/2.0);
}

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
    calculate_midpoint;
}

void Line::set_p2( Point p2 )
{
    this -> p2 = p2;
    calculate_midpoint;
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
    calculate_midpoint();
}

void Line::rotate2D( float yaw )
{
    this -> yaw += yaw;
    while(this -> yaw < 0 )
        yaw +=  ( M_PI *2 );
    while( this -> yaw >  ( M_PI * 2 ) )
        yaw -= ( M_PI * 2  )
    }

void Line::move2D( float x, float y, float yaw );
{
    p1.x += x;
    p2.x += x;

    p1.y += y;
    p2.y += y;

    p1.yaw += yaw;
    while(p1.yaw < 0 )
        p1.yaw +=  ( M_PI << 1 );
    while( p1.yaw >  ( M_PI << 1 ) )
        p1.yaw -= ( M_PI << 1 )
                  calculate_midpoint();
}

void Line::translate2Dp1(float x, float y)
{
    p1.x += x;
    p1.y += y;
    calculate_midpoint();
}

void Line::translate2Dp2(float x, float y)
{
    p2.x += x;
    p2.y += y;
    calculate_midpoint();
}

void Line::move2Dp1( float x, float y, float yaw)
{
    p1.x += x;
    p1.y += y;
    this -> yaw += yaw;
    while(this -> yaw < 0 )
        yaw +=  ( M_PI * 2 );
    while( this -> yaw >  ( M_PI * 2 ) )
        yaw -= ( M_PI * 2 )

    }

void Line::move2Dp2( float x, floaty, float yaw)
{
    p2.x += x;
    p2.y += y;
    this -> yaw += yaw;
    while(this -> yaw < 0 )
        yaw +=  ( M_PI * 2  );
    while( this -> yaw >  ( M_PI * 2 ) )
        yaw -= ( M_PI * 2 )

    }
