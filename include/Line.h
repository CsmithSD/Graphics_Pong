#ifndef _LINE_H_
#define _LINE_H_

#include "Entity2D.h"
#include "Point.h"
#include "Color.h"
#include <math.h>
class Line : public Entity2D
{
    public:
        line( Point2D p1 = Point2D(), Point2D p2 = Point2D(), Color color = Color( 1,1,1 ), Velocity2D vel = Veocity2D );
        ~line();

        void draw();
        void set_color( float r = 1, float g = 1, float b = 1 );
        void set_p1( Point p1 );
        void set_p2( Point p2 );

        Point get_p1( );
        Point get_p2( );

        //Implemented virtual functions
        void translate2D( float x, float y);
        void rotate2D( float yaw);
        void move2D( float x, float y, float yaw);

        float translate2Dp1( float x, float y);
        float translate2Dp2( float x, float y);

        float move2Dp1(float x, float y, float yaw);
        float move2Dp2(float x, float y, float yaw);

    protected:
        Point2D p1;
        Point2D p2;
        Point2D midpoint;
        Color color;
        void calculate_midpoint();
}

#endif
