/*
                    ***** OpenGLDemo.cpp*****

OpenGL graphics program, illustrating use of GLUT and callback functions.

CSC433/533 Computer Graphics - Fall 2014

Author: John M. Weiss, Ph.D.
Originally written January 20, 2006.

Modifications:
*/

// include files
#include <iostream>
using namespace std;

// the GLUT header automatically includes gl.h and glu.h
#include <GL/freeglut.h>

// symbolic constants
// define PI for stupid Windows compilers that do not supply it
#ifndef M_PI
const float M_PI = 3.14159265358979323846;
#endif

// keypresses
const int EscapeKey = 27;

// colors
const float Black[]     = { 0.0, 0.0, 0.0 };
const float Red[]       = { 1.0, 0.0, 0.0 };
const float Green[]     = { 0.0, 1.0, 0.0 };
const float Blue[]      = { 0.0, 0.0, 1.0 };
const float Magenta[]   = { 1.0, 0.0, 1.0 };
const float Cyan[]      = { 0.0, 1.0, 1.0 };
const float Yellow[]    = { 1.0, 1.0, 0.0 };
const float White[]     = { 1.0, 1.0, 1.0 };

// world coordinate window extents: -1000 to +1000 in smaller dimension
const float ViewplaneSize = 1000.0;

// global vars
int ScreenWidth  = 500;
int ScreenHeight = 500;

// OpenGL callback function prototypes
void display( void );
void reshape( int w, int h );
void keyboard( unsigned char key, int x, int y );
void mouseclick( int button, int state, int x, int y );
void mousedrag( int x, int y );

// useful graphics function prototypes
void initOpenGL( void );
void DrawLine( float x1, float y1, float x2, float y2, const float color[] );
void DrawRectangle( float x1, float y1, float x2, float y2, const float color[] );
void DrawFilledRectangle( float x1, float y1, float x2, float y2, const float color[] );
void DrawEllipse( float xRadius, float yRadius, int x, int y, const float color[] );
void DrawFilledEllipse( float xRadius, float yRadius, int x, int y, const float color[] );
void DrawBitmapString( const char *string, float x, float y, const float color[] );
void DrawStrokeString( const char *string, float x, float y, const float color[] );

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
    glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE ); // 32-bit graphics and single buffering

    glutInitWindowSize( ScreenWidth, ScreenHeight );    // initial window size
    glutInitWindowPosition( 100, 50 );          // initial window position
    glutCreateWindow( "OpenGL Demo" );          // window title

    glClearColor( 0.0, 0.0, 0.0, 1.0 );         // use black for glClear command

    // callback routines
    glutDisplayFunc( display );             // how to redisplay window
    glutReshapeFunc( reshape );             // how to resize window
    glutKeyboardFunc( keyboard );           // how to handle key presses
    glutMouseFunc( mouseclick );            // how to handle mouse events
}

/******************************************************************************/
/*                          OpenGL callback functions                         */
/******************************************************************************/

// callback function that tells OpenGL how to redraw window
void display( void )
{
    // clear the display
    glClear( GL_COLOR_BUFFER_BIT );

    // draw a line, rectangles, and ellipses
    // note that objects are resized with window
    DrawLine( -ViewplaneSize + 10, -ViewplaneSize + 20, ViewplaneSize - 10, ViewplaneSize - 20, Yellow );
    DrawRectangle( 300, 200, 900, 400, Cyan );
    DrawFilledRectangle( -700, -100, -400, -800, Red );
    DrawEllipse( 300, 200, 600, -300, Green );
    DrawFilledEllipse( 300, 200, -600, 300, Magenta );

    // label display with text
    DrawStrokeString( "OpenGL Demo (stroke)", -0.9 * ViewplaneSize, 0.8 * ViewplaneSize, White );
    DrawBitmapString( "OpenGL Demo (bitmap)", -0.1 * ViewplaneSize, -0.8 * ViewplaneSize, White );

    // flush graphical output
    glFlush();
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
        gluOrtho2D( -ViewplaneSize * w / h, ViewplaneSize * w / h, -ViewplaneSize, ViewplaneSize );
    else
        gluOrtho2D( -ViewplaneSize, ViewplaneSize, -ViewplaneSize * h / w, ViewplaneSize * h / w );
    glViewport( 0, 0, w, h );           // adjust viewport to new window
}

/******************************************************************************/

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

/******************************************************************************/
/*                          useful graphics routines                          */
/******************************************************************************/

// draw a line using the given RGB color value
void DrawLine( float x1, float y1, float x2, float y2, const float color[] )
{
    glColor3fv( color );
    glBegin( GL_LINES );
        glVertex2f( x1, y1 );
        glVertex2f( x2, y2 );
    glEnd();
    glFlush();
}

/******************************************************************************/

// draw a rectangle using the given RGB color value
void DrawRectangle( float x1, float y1, float x2, float y2, const float color[] )
{
    glColor3fv( color );
    glBegin( GL_LINE_LOOP );
        glVertex2f( x1, y1 );
        glVertex2f( x2, y1 );
        glVertex2f( x2, y2 );
        glVertex2f( x1, y2 );
    glEnd();
    glFlush();
}

/******************************************************************************/

// draw a filled rectangle using the given RGB color value
void DrawFilledRectangle( float x1, float y1, float x2, float y2, const float color[] )
{
    glColor3fv( color );
    glRectf( x1, y1, x2, y2 );
    /* or draw a polygon:
    glBegin( GL_POLYGON );
        glVertex2f( x1, y1 );
        glVertex2f( x2, y1 );
        glVertex2f( x2, y2 );
        glVertex2f( x1, y2 );
    glEnd();
    */
    glFlush();
}

/******************************************************************************/

// draw an ellipse of given radii at a specified position using the given RGB color value
void DrawEllipse( float xRadius, float yRadius, int x, int y, const float color[] )
{
    float radius = xRadius < yRadius ? xRadius : yRadius;   // stretch circle into ellipse
    glColor3fv( color );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( x, y, 0 );
    glScalef( xRadius / radius, yRadius / radius, 1.0 );    // by ratio of major to minor axes
    GLUquadricObj *disk = gluNewQuadric();
    gluDisk( disk, radius - 4, radius, int( radius ), 1 );
    gluDeleteQuadric( disk );
    glLoadIdentity();
    glFlush();
}

/******************************************************************************/

// draw an ellipse of given radii at a specified position using the given RGB color value
void DrawFilledEllipse( float xRadius, float yRadius, int x, int y, const float color[] )
{
    float radius = xRadius < yRadius ? xRadius : yRadius;   // stretch circle into ellipse
    glColor3fv( color );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( x, y, 0 );
    glScalef( xRadius / radius, yRadius / radius, 1.0 );    // by ratio of major to minor axes
    GLUquadricObj *disk = gluNewQuadric();
    gluDisk( disk, 0, radius, int( radius ), 1 );
    gluDeleteQuadric( disk );
    glLoadIdentity();
    glFlush();
}

/******************************************************************************/

// write a text string at a specified position using the given RGB color value
void DrawBitmapString( const char *string, float x, float y, const float color[] )
{
    glColor3fv( color );
    glRasterPos2f( x, y );

    // glutBitmapString is available in freeglut
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char *)string );

    // GLUT only supports glutBitmapCharacter
    // while ( *string ) glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *string++ );
}

void DrawStrokeString( const char *string, float x, float y, const float color[] )
{
    glColor3fv( color );
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef( x, y, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)string );
    glPopMatrix();
}

