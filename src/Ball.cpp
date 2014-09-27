#include "../include/Ball.h"


Ball::Ball(Point2D point, float radius, Color color, Velocity2D vel ):
    FilledCircle(point,radius,color,vel)
{
    left_limit = 0;
    right_limit = 0;
    top_limit = 0;
    bottom_limit = 0;
}

Ball::~Ball()
{

}

void Ball::animate(float timestep)
{
    point.x += vel.x_vel * timestep;
    point.y += vel.y_vel * timestep;
    point.yaw += vel.yaw_vel * timestep;

    if( point.x <= left_limit )
    {
        vel.x_vel *= -1;
        point.x += left_limit - point.x;
    }
    else if( point.x >= right_limit )
    {
        vel.x_vel *= -1;
        point.x += right_limit - point.x;
    }
    if( point.y <= bottom_limit )
    {
        vel.y_vel *= -1;
        point.y += bottom_limit - point.y;
    }
    else if( point.y >= top_limit )
    {
        vel.y_vel *= -1;
        point.y += top_limit - point.y;
    }
}

void Ball::set_limits(float left, float right, float bottom, float top)
{
    left_limit = left;
    right_limit = right;
    top_limit = top;
    bottom_limit = bottom;
}

void Ball::check_paddle_collision( const Paddle* paddle )
{
    float paddle_x = (Entity2D*) (paddle)->get_x();
    float paddle_y = paddle->get_y();
    float paddle_yaw = paddle->get_yaw();
    Velocity2D paddle_vel = paddle -> get_velocity();
    float width = paddle->get_width();
    float height = paddle->get_height();

    float x,y,rotated_x,rotated_y;
    //Precalculate sin and cos, 1/2 w and h
    float c = cos(paddle_yaw);
    float s = sin(paddle_yaw);
    float w = 0.5 * width  + radius ;
    float h = 0.5 * height + radius ;

    float distance[4];
    float shortest_distance = -1;
    Point2D bl_corner;
    Point2D tl_corner;
    Point2D tr_corner;
    Point2D br_corner;

    //Bottom Left Corner
    x = - w;
    y = - h;
    rotated_x = x*c - y*s;
    rotated_y = x*s + y*c;

    bl_corner.x = rotated_x + paddle_x;
    bl_corner.y = rotated_y + paddle_y;

    //Top Left Corner
    //x = w; - don't need to recalculate
    y = h;
    rotated_x = x*c - y*s;
    rotated_y = x*s + y*c;

    bl_corner.x = rotated_x + paddle_x;
    bl_corner.y = rotated_y + paddle_y;

    //Top Right Corner
    x = w;
    //y = point.y + h; - don't need to recalculate
    rotated_x = x*c - y*s;
    rotated_y = x*s + y*c;

    tr_corner.x = rotated_x + paddle_x;
    tr_corner.y = rotated_y + paddle_y;

    //Bottom Right Corner
    //x = point.x + w; - don't need to recalculate
    y = - h;
    rotated_x = x*c - y*s;
    rotated_y = x*s + y*c;

    br_corner.x = rotated_x + paddle_x;
    br_corner.y = rotated_y + paddle_y;

    distance[0] = calc_distance( bl_corner, tl_corner );
    distance[1] = calc_distance( tl_corner, tr_corner );
    distance[2] = calc_distance( tr_corner, br_corner );
    distance[3] = calc_distance( br_corner, bl_corner );
    
    if( distance[1] < ( h * 2 ) && distance[3] < ( h * 2 ) )
    {
        if( distance[0] < radius )
        {
            vel.x_vel*=-1;
            vel.y_vel*=-1;
        }
        else if( distance[2] < radius )
        {
            vel.x_vel*=-1;
            vel.y_vel*=-1;
        }
   }
    if( distance[0] < ( w << 1 ) && distance[2] < ( w << 1 ) )
    {
        if( distance[1] < radius )
        {
            vel.x_vel*=-1;
            vel.y_vel*=-1;
        }
        else if( distance[3] < radius )
        {
            vel.x_vel*=-1;
            vel.y_vel*=-1;
        }
   }
}
float Ball::calc_distance(Point2D p1, Point2D p2)
{
    float distance = ( (p2.y - p1.y)*point.x - ( p2.x - p1.x )*point.y - p1.x*p2.y + p2.x*p1.y);
    if( distance < 0 )
        distance *=-1;

    distance /= sqrt( ( p2.x - p1.x ) * ( p2.x -p1.x ) + ( p2.y - p1.y ) * ( p2.y -p1.y ) )
    return distance;
}
