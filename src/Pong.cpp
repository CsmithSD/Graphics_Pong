//Class include files
#include "../include/Paddle.h"
#include "../include/Ball.h"
//#include "../include/Point2D.h"
//#include "../include/Velocity2D.h"
// include files c/c++ libraries
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

#define PADDLE_WIDTH 2
#define PADDLE_HEIGHT 15
#define GAME_HEIGHT 100
#define GAME_WIDTH 100
#define PADDLE_SPEED 2
#define BALL_START_SPEED 4
// the GLUT header automatically includes gl.h and glu.h
#include <GL/freeglut.h>

// keypresses
const int EscapeKey = 27;
// world coordinate window extents: -1000 to +1000 in smaller dimension

Ball ball(Point2D(GAME_WIDTH/2.0,GAME_HEIGHT/2.0),1,Color(1,0,0));
Paddle left_paddle(Point2D(PADDLE_WIDTH,GAME_HEIGHT/2.0),PADDLE_WIDTH,PADDLE_HEIGHT,Color(0,1,0));
Paddle right_paddle(Point2D(GAME_WIDTH - PADDLE_WIDTH, GAME_HEIGHT/2.0),PADDLE_WIDTH,PADDLE_HEIGHT,Color(0,0,1));
//Game state variable
int GAMESTATE = 0;

// global vars
int ScreenWidth  = 600;
int ScreenHeight = 600;

// OpenGL callback function prototypes
void display( void );
void reshape( int w, int h );
void keyboard( unsigned char key, int x, int y );
void special_keyboard( int key, int x, int y);
void mouseclick( int button, int state, int x, int y );
void mousedrag( int x, int y );
void idle();

// useful graphics function prototypes
void initOpenGL( void );

/******************************************************************************/

// main() function
int main( int argc, char *argv[] )
{
    left_paddle.set_limits(0,GAME_WIDTH/2.0,0,GAME_HEIGHT);
    right_paddle.set_limits(GAME_WIDTH/2.0,GAME_WIDTH,0,GAME_HEIGHT);
    ball.set_limits(-ball.get_radius(),GAME_WIDTH+ball.get_radius(),0,GAME_HEIGHT);
    // perform various OpenGL initializations
    glutInit( &argc, argv );
    initOpenGL();

    // go into OpenGL/GLUT main loop, never to return
    glutMainLoop();

    // yeah I know, but it keeps compilers from bitching
    return 0;
}

/******************************************************************************/

// various commands to initialize OpenGL and GLUT
void initOpenGL( void )
{
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE ); // 32-bit graphics and single buffering

    glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( 100, 50 );          // initial window position
    glutCreateWindow( "OpenGL Demo" );          // window title

    glClearColor( 0.0, 0.0, 0.0, 1.0 );         // use black for glClear command

    // callback routines
    glutDisplayFunc( display );             // how to redisplay window
    glutReshapeFunc( reshape );             // how to resize window
    glutKeyboardFunc( keyboard );           // how to handle key presses
    glutSpecialFunc( special_keyboard);     // how to handle arrow keys
    glutMouseFunc( mouseclick );            // how to handle mouse events
    glutIdleFunc( idle );
}

/******************************************************************************/
/*                          OpenGL callback functions                         */
/******************************************************************************/

// callback function that tells OpenGL how to redraw window
void display( void )
{
    // clear the display
    glClear( GL_COLOR_BUFFER_BIT );
    ball.draw();
    left_paddle.draw();
    right_paddle.draw();
    //for(int i = 0; i < num_entities; i++)
    //  entities[i].draw();

    // flush graphical output
    glutSwapBuffers();
    glFlush();
}

void idle()
{
    //We want the screen to update as quickly as possible, but
    //scale the motion to the amount of time between frames.
    //We define "Normal" as 25 frames per second and scale based on that
    static clock_t last_time = clock();
    clock_t new_time = clock();
    clock_t delta = new_time - last_time;
    float scale_factor = ((float)delta/CLOCKS_PER_SEC)/(0.04);
    //for(int i = 0; i < num_entities; i++)
    //  entities[i].animate();
    last_time = new_time;
    glFlush();
    glutPostRedisplay();
}

/******************************************************************************/

// callback function that tells OpenGL how to resize window
// note that this is called when the window is first created
void reshape( int w, int h )
{
    // store new window dimensions globally
    ScreenWidth = w;
    ScreenHeight = h;

    // how to project 3-D scene onto 2-D
    glMatrixMode( GL_PROJECTION );      // use an orthographic projection
    glLoadIdentity();                   // initialize transformation matrix
    if ( w > h )                        // use width:height aspect ratio to specify view extents
        gluOrtho2D( 0, GAME_WIDTH * w / h, 0, GAME_HEIGHT );
    else
        gluOrtho2D( 0, GAME_WIDTH, 0, GAME_HEIGHT * h / w );
    glViewport( 0, 0, w, h );           // adjust viewport to new window
}

/******************************************************************************/

void special_keyboard( int key, int x, int y)
{
    y = ScreenHeight -y;
    cerr << "Special Keypress: " << key << " (" << int( key ) << ") at (" << x << "," << y << ")\n";

    switch(key)
    {
        case GLUT_KEY_LEFT:
            right_paddle.set_velocity(-PADDLE_SPEED,
        break;

        case GLUT_KEY_RIGHT:

        break;

        case GLUT_KEY_UP:

        break;

        case GLUT_KEY_DOWN:

        break;

    }
}

void keyboardUp(unsigned char key, int x, int y)
{
    y = ScreenHeight -y;
    cerr << "Special KeyRelease: " << key << " (" << int(key) << ") at (" << x << "," << y << ")\n";

    Velocity2D left = left_paddle.get_velocity();
    switch(key)
    {
        case 'a':
        case 'A':
            left_paddle.set_velocity(left.x_vel+PADDLE_SPEED,left.y_vel,left.yaw_vel);
        break;

        case 's':
        case 'S':
            left_paddle.set_velocity(left.x_vel,left.y_vel+PADDLE_SPEED,left.yaw_vel);
        break;

        case 'd':
        case 'D':

        break;

        case 'w':
        case 'W':

        break;
    }
}

// callback function that tells OpenGL how to handle keystrokes
void keyboard( unsigned char key, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;
    cerr << "keypress: " << key << " (" << int( key ) << ") at (" << x << "," << y << ")\n";

    // process keypresses
    switch ( key )
    {
        // Escape quits program
        case EscapeKey:
            exit( 0 );
            break;

        case 'a':
        case 'A':

        break;

        case 's':
        case 'S':

        break;

        case 'd':
        case 'D':

        break;

        case 'w':
        case 'W':

        break;

        case ' ':
        case 'p':
        case 'P':

        break;


        // anything else redraws window
        default:
            glutPostRedisplay();
            break;
    }
}

/******************************************************************************/

// callback function for mouse button click events
void mouseclick( int button, int state, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;

    // handle mouse click events
    switch ( button )
    {
        case GLUT_LEFT_BUTTON:              // left button
            if ( state == GLUT_DOWN )           // press
                cerr << "mouse click: left press at    (" << x << "," << y << ")\n";
            else if ( state == GLUT_UP )        // release
                cerr << "mouse click: left release at  (" << x << "," << y << ")\n";
            break;

        case GLUT_RIGHT_BUTTON:             // right button
            if ( state == GLUT_DOWN )           // press
                cerr << "mouse click: right press at   (" << x << "," << y << ")\n";
            else if ( state == GLUT_UP )        // release
                cerr << "mouse click: right release at (" << x << "," << y << ")\n";
            break;
    }
}
