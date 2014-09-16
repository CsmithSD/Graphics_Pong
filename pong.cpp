


//Include Files
#include <iostream>

//Class include Files


using namespace std;



// use OpenGL graphics and the GLUT graphical user interface
#include <GL/glut.h>

// constants
const int EscapeKey = 27;

/******************************************************************************/

// global classes
int WindowHeight = 400;
int startx, starty, endx, endy;
// function prototypes

// GLUT callbacks
void display();
void reshape( int w, int h );
void keyboard( unsigned char key, int x, int y );

/******************************************************************************/

// main() function

int main( int argc, char *argv[])
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );

    // Pong window
    glutInitWindowSize( 400, 400 );
    glutInitWindowPosition( 0, 100 );
    int pong = glutCreateWindow( "Pong" );

    // Pong Callbacks
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );

    // go into OpenGL/GLUT main loop, never to return
    glutMainLoop(  );

    return 0;
}


/******************************************************************************/
/*                          OpenGL callback functions                         */
/******************************************************************************/

// callback function that tells OpenGL how to redraw window 1
void display()
{
    // redraw the rectangle in yellow
    glClear( GL_COLOR_BUFFER_BIT );
    glColor3f( 1.0, 1.0, 0.0 );
    glRecti( startx, starty, endx, endy );
    glFlush();
    glutSwapBuffers();
}


// callback function that tells OpenGL how to resize either window
void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, w, 0.0, h );
    
    WindowHeight = h;
}



void keyboard( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case EscapeKey:
            exit( 0 );
            break;
        default:
            cout << "You pressed key " << key << " Pong's Window\n";
            break;
    }
}










