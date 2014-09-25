//Class include files
#include "../include/Paddle.h"
#include "../include/Circle.h"
//#include "../include/Point2D.h"
//#include "../include/Velocity2D.h"
// include files c/c++ libraries
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

// the GLUT header automatically includes gl.h and glu.h
#include <GL/freeglut.h>

// keypresses
const int EscapeKey = 27;

//TEST PADDLE
Point2D left_start(250,250,-976);
Paddle Left_paddle(left_start, 100, 50);

// world coordinate window extents: -1000 to +1000 in smaller dimension
const float ViewplaneSize = 1000.0;

// global vars
int ScreenWidth  = 500;
int ScreenHeight = 500;

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
    Left_paddle.draw();
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
    Left_paddle.animate(scale_factor);
    //for(int i = 0; i < num_entities; i++)
    //  entities[i].animate();
    last_time = new_time;
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
        gluOrtho2D( 0, ViewplaneSize * w / h, 0, ViewplaneSize );
    else
        gluOrtho2D( 0, ViewplaneSize, 0, ViewplaneSize * h / w );
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

        break;

        case GLUT_KEY_RIGHT:

        break;

        case GLUT_KEY_UP:

        break;

        case GLUT_KEY_DOWN:

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
