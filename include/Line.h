#include "Entity2D.h"
#include "Point.h"
#include "Color.h"
#include <math.h>
class Line : public Entity2D
{
    public:
        line( Point p1 = Point(), Point p2 = Point(), Color color = Color( 1,1,1 ) );
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
        Point p1;
        Point p2;
        Color color;
}
