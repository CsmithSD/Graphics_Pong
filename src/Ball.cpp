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
    goal = 0;
    if( point.x <= left_limit )
    {
        goal = 1;
    }
    else if( point.x >= right_limit )
    {
        goal = 2;
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

int Ball::goal_made() {
    return goal;
}

void Ball::set_limits(float left, float right, float bottom, float top)
{
    left_limit = left;
    right_limit = right;
    top_limit = top;
    bottom_limit = bottom;
}

bool Ball::check_paddle_collision( Paddle& paddle , float ball_scale_factor, float paddle_scale_factor)
{
    float distance[4];
    Point2D bl,br,tl,tr;
    paddle.get_corners(bl,br,tl,tr);

    distance[0] = calc_distance( bl, tl );
    distance[1] = calc_distance( tl, tr);
    distance[2] = calc_distance( tr, br);
    distance[3] = calc_distance( br, bl );

    //check left/right envelope
    if(distance[1] > paddle.get_height() + 2*radius || distance[3] > paddle.get_height() + 2*radius)
    {
        //no collision, return
        return false;
    }

    //check up/down envelope
    if(distance[0] > paddle.get_width() + 2*radius || distance[2] > paddle.get_width() + 2*radius)
    {
        //no collision, return
        return false;
    }

    //first, step the ball back to where it was on the previous time step
    //to try to avoid getting inside the paddle
    translate2D(-vel.x_vel*ball_scale_factor,-vel.y_vel*ball_scale_factor);

    //If we reach here, the ball has collided with the paddle and needs to reflect
    //assume we hit the edge with the smallest distance
    int min_index = 0;
    int min_distance = distance[0];
    for(int i = 1; i < 4; i++)
    {
        if(distance[i] < min_distance)
        {
            min_distance = distance[i];
            min_index = i;
        }
    }
    float paddle_angle = paddle.get_yaw();
    float new_angle;
    if(1 == min_index || 3 == min_index)
        paddle_angle += M_PI/2.0;

    float bat = atan2(vel.y_vel,vel.x_vel);
    //flip the ball's direction of travel, this makes the math nice
    //this also puts us in the range [0,2pi] instead of [-pi,pi]
    bat = bat + M_PI;

    //we want to find the difference between the vector normal to the paddle and
    //the ball's inverted angle of travel
    if(abs(bat - paddle_angle) < abs(paddle_angle - bat))
    {
        new_angle = paddle_angle + (bat - paddle_angle);
    }
    else
    {
        new_angle = paddle_angle + (paddle_angle - bat);
    }

    float old_vel_mag = sqrt(vel.x_vel*vel.x_vel + vel.y_vel*vel.y_vel);
    vel.x_vel = old_vel_mag*cos(new_angle);
    vel.y_vel = old_vel_mag*sin(new_angle);

    //Now, just nudge the ball back out of the paddle so it doesn't get
    //stuck in the paddle or go through it
    //first, move the ball by the same velocity as the paddle to prevent the paddle from
    //moving into the ball's space
    Velocity2D paddle_vel = paddle.get_velocity();
    translate2D(paddle_vel.x_vel*paddle_scale_factor*1.5,paddle_vel.y_vel*paddle_scale_factor*1.5);

    float offset_distance=0;
    switch(min_index)
    {
    //back side
    case 0:
        offset_distance = (distance[0] - radius)*1.5;
        paddle_angle = paddle.get_yaw() + M_PI;
        break;
    //top
    case 1:
        offset_distance = (distance[1] - radius)*1.5;
        paddle_angle = paddle.get_yaw() + M_PI/2.0;
        break;
    //front
    case 2:
        offset_distance = (distance[2] - radius)*1.5;
        paddle_angle = paddle.get_yaw();
        break;
    //bottom
    case 3:
        offset_distance = (distance[3] - radius)*1.5;
        paddle_angle = paddle.get_yaw() - M_PI/2.0;
        break;
    }

    translate2D(offset_distance*cos(paddle_angle),offset_distance*sin(paddle_angle));
    return true;
}

//Calculate perpendicular distance from a line defined by two points
//to another point
float Ball::calc_distance(Point2D p1, Point2D p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float distance = ( dy*point.x - dx*point.y - (p1.x*p2.y) + ( p2.x*p1.y ) );
    if( distance < 0 )
        distance *=-1;

    distance /= sqrt( dx * dx + dy * dy );
    return distance;
}
