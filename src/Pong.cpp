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

#define PADDLE_WIDTH 45
#define PADDLE_HEIGHT 160
#define TOTAL_WIDTH 1600
#define TOTAL_HEIGHT 1600
#define BOTTOM_COURT_EDGE 300
#define TOP_COURT_EDGE 1200
#define PADDLE_SPEED 500
#define BALL_START_SPEED 40
#define PADDLE_ROTATE_SPEED 1.5
#define BALL_SIZE 5
// the GLUT header automatically includes gl.h and glu.h
#include <GL/freeglut.h>

// keypresses
const int EscapeKey = 27;
// world coordinate window extents: -1000 to +1000 in smaller dimension

Ball ball(Point2D(TOTAL_WIDTH/2.0,TOTAL_HEIGHT/2.0),BALL_SIZE,Color(1,0,0),Velocity2D(500,500,0));
Paddle left_paddle(Point2D(PADDLE_WIDTH,TOTAL_HEIGHT/2.0),PADDLE_WIDTH,PADDLE_HEIGHT,Color(0,1,0));
Paddle right_paddle(Point2D(TOTAL_WIDTH - PADDLE_WIDTH, TOTAL_HEIGHT/2.0),PADDLE_WIDTH,PADDLE_HEIGHT,Color(0,0,1));
//Game state variable
//0 - Game Not Started
//1 - Game In Progress
//2 - Game Ended
float BALL_WARP = 1;
float PADDLE_WARP = 1;
int GAMESTATE = 0;
bool PAUSED = false;
// global vars
int ScreenWidth  = 600;
int ScreenHeight = 600;

// OpenGL callback function prototypes
void showStartScreen();
void showPausedStr();
void display( void );
void reshape( int w, int h );
void keyboard( unsigned char key, int x, int y );
void keyboardUp( unsigned char key, int x, int y);
void special_keyboard( int key, int x, int y);
void special_keyboardUp( int key, int x, int y);
void mouseclick( int button, int state, int x, int y );
void mousedrag( int x, int y );
void idle();
void draw_outline();

// useful graphics function prototypes
void initOpenGL( void );

/******************************************************************************/

// main() function
int main( int argc, char *argv[] )
{
    left_paddle.set_limits(0,TOTAL_WIDTH/2.0,BOTTOM_COURT_EDGE, TOP_COURT_EDGE);
    right_paddle.set_limits(TOTAL_WIDTH/2.0,TOTAL_WIDTH,BOTTOM_COURT_EDGE, TOP_COURT_EDGE);
    ball.set_limits(-ball.get_radius(),TOTAL_WIDTH+ball.get_radius(),BOTTOM_COURT_EDGE,TOP_COURT_EDGE);
    // perform various OpenGL initializations
    glutInit( &argc, argv );
    initOpenGL();
    glutIgnoreKeyRepeat(1);//ignore auto repeats from held keys

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
    glutKeyboardUpFunc( keyboardUp);
    glutSpecialFunc( special_keyboard);     // how to handle arrow keys
    glutSpecialUpFunc( special_keyboardUp);
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
    switch(GAMESTATE)
    {
        //Game not yet started
        case 0:       
            showStartScreen();
            //Display Name
            //Display Controls
            break;

    }
    if(PAUSED)
    {
        showPausedStr();
    }
    glClear( GL_COLOR_BUFFER_BIT );
    left_paddle.draw();
    right_paddle.draw();
    draw_outline();
    ball.draw();
    glFlush();
    glutSwapBuffers();
}

void draw_outline()
{
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    //bottom left
    glVertex2f(0,BOTTOM_COURT_EDGE);

    //bottom right
    glVertex2f(TOTAL_WIDTH,BOTTOM_COURT_EDGE);

    //Top right
    glVertex2f(0,TOP_COURT_EDGE);

    //top left 
    glVertex2f(TOTAL_WIDTH,TOP_COURT_EDGE);
    glEnd();
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

    if(GAMESTATE == 1 && !PAUSED)
    {
        ball.animate(scale_factor*BALL_WARP);
        left_paddle.animate(scale_factor*PADDLE_WARP);
        if(ball.check_paddle_collision( left_paddle , scale_factor*BALL_WARP, scale_factor*PADDLE_WARP))
            left_paddle.shrink();
        right_paddle.animate(scale_factor*PADDLE_WARP);
        if(ball.check_paddle_collision( right_paddle , scale_factor*BALL_WARP, scale_factor*PADDLE_WARP))
            right_paddle.shrink();
    }
    last_time = new_time;
    glutPostRedisplay();
}

void showPausedStr()
{
    glColor3f(1,1,1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef( 100, 100, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"***PAUSED***" );
    glPopMatrix();
}

void showStartScreen()
{
    glColor3f(1,1,1 );
    glRasterPos2f( 100, 100 );

    // glutBitmapString is available in freeglut
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char *)"test2asdfasdfasdt");

    // GLUT only supports glutBitmapCharacter
    // while ( *string ) glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *string++ );
}

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
    float extra_x;
    float extra_y;
    if ( w > h )                        // use width:height aspect ratio to specify view extents
    {
        extra_x = w-h;
        extra_y = 0;
        gluOrtho2D( 0, TOTAL_WIDTH*w/h, 0, TOTAL_HEIGHT );
    }
    else
    {
        extra_x = 0;
        extra_y = h-w;
        gluOrtho2D( 0, TOTAL_WIDTH, 0, TOTAL_HEIGHT * h / w );
    }
    glViewport( extra_x/2, extra_y-2, w, h );           // adjust viewport to new window
}

/******************************************************************************/

void special_keyboard( int key, int x, int y)
{
    y = ScreenHeight -y;
    cerr << "Special Keypress: " << key << " (" << int( key ) << ") at (" << x << "," << y << ")\n";

    Velocity2D right = right_paddle.get_velocity();
    switch(key)
    {
        case GLUT_KEY_HOME:
            right.yaw_vel += PADDLE_ROTATE_SPEED;
            break;
        case GLUT_KEY_PAGE_UP:
            right.yaw_vel -= PADDLE_ROTATE_SPEED;
            break;
        case GLUT_KEY_LEFT:
            right.x_vel -= PADDLE_SPEED;
            break;
        case GLUT_KEY_RIGHT:
            right.x_vel += PADDLE_SPEED;
            break;
        case GLUT_KEY_UP:
            right.y_vel += PADDLE_SPEED;
            break;
        case GLUT_KEY_DOWN:
        case GLUT_KEY_BEGIN:
            right.y_vel -= PADDLE_SPEED;
            break;
    }

    //Make sure we didn't allow a double press
    //Also allows recovery if there was a dropped release or press
    if(right.x_vel > PADDLE_SPEED)
        right.x_vel = PADDLE_SPEED;
    if(right.x_vel < -PADDLE_SPEED)
        right.x_vel = -PADDLE_SPEED;

    if(right.y_vel > PADDLE_SPEED)
        right.y_vel = PADDLE_SPEED;
    if(right.y_vel < -PADDLE_SPEED)
        right.y_vel = -PADDLE_SPEED;

    if(right.yaw_vel > PADDLE_ROTATE_SPEED)
        right.yaw_vel = PADDLE_ROTATE_SPEED;
    if(right.yaw_vel < -PADDLE_ROTATE_SPEED)
        right.yaw_vel = -PADDLE_ROTATE_SPEED;

    //apply velocity changes
    right_paddle.set_velocity(right.x_vel, right.y_vel, right.yaw_vel);
}

void special_keyboardUp( int key, int x, int y)
{
    y = ScreenHeight -y;
    cerr << "Special KeyRelease: " << key << " (" << int( key ) << ") at (" << x << "," << y << ")\n";

    Velocity2D right = right_paddle.get_velocity();
    switch(key)
    {
        case GLUT_KEY_HOME:
            right.yaw_vel -= PADDLE_ROTATE_SPEED;
            break;
        case GLUT_KEY_PAGE_UP:
            right.yaw_vel += PADDLE_ROTATE_SPEED;
            break;
        case GLUT_KEY_LEFT:
            right.x_vel += PADDLE_SPEED;
            break;
        case GLUT_KEY_RIGHT:
            right.x_vel -= PADDLE_SPEED;
            break;
        case GLUT_KEY_UP:
            right.y_vel -= PADDLE_SPEED;
            break;
        case GLUT_KEY_DOWN:
        case GLUT_KEY_BEGIN:
            right.y_vel += PADDLE_SPEED;
            break;
    }

    //Make sure we didn't allow a double press
    //Also allows recovery if there was a dropped release or press
    if(right.x_vel > PADDLE_SPEED)
        right.x_vel = PADDLE_SPEED;
    if(right.x_vel < -PADDLE_SPEED)
        right.x_vel = -PADDLE_SPEED;

    if(right.y_vel > PADDLE_SPEED)
        right.y_vel = PADDLE_SPEED;
    if(right.y_vel < -PADDLE_SPEED)
        right.y_vel = -PADDLE_SPEED;

    if(right.yaw_vel > PADDLE_ROTATE_SPEED)
        right.yaw_vel = PADDLE_ROTATE_SPEED;
    if(right.yaw_vel < -PADDLE_ROTATE_SPEED)
        right.yaw_vel = -PADDLE_ROTATE_SPEED;

    //apply velocity changes
    right_paddle.set_velocity(right.x_vel, right.y_vel, right.yaw_vel);
}

void keyboardUp(unsigned char key, int x, int y)
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;
    cerr << "keyrelease: " << key << " (" << int( key ) << ") at (" << x << "," << y << ")\n";

    Velocity2D left = left_paddle.get_velocity();
    Velocity2D right = right_paddle.get_velocity();
    // process keypresses
    switch ( key )
    {
        case 'a':
        case 'A':
            left.x_vel += PADDLE_SPEED;
            break;
        case 'd':
        case 'D':
            left.x_vel -= PADDLE_SPEED;
            break;
        case 's':
        case 'S':
            left.y_vel += PADDLE_SPEED;
            break;
        case 'w':
        case 'W':
            left.y_vel -= PADDLE_SPEED;
            break;
        case 'q':
        case 'Q':
            left.yaw_vel -= PADDLE_ROTATE_SPEED;
            break;
        case 'e':
        case 'E':
            left.yaw_vel += PADDLE_ROTATE_SPEED;
            break;

            //Right Paddle Keys
        case '7':
            right.yaw_vel -= PADDLE_ROTATE_SPEED;
            break;
        case '9':
            right.yaw_vel += PADDLE_ROTATE_SPEED;
            break;
        case '4':
            right.x_vel += PADDLE_SPEED;
            break;
        case '6':
            right.x_vel -= PADDLE_SPEED;
            break;
        case '5':
            right.y_vel += PADDLE_SPEED;
            break;
        case '8':
            right.y_vel -= PADDLE_SPEED;
            break;
    }
    if(left.x_vel > PADDLE_SPEED)
        left.x_vel = PADDLE_SPEED;
    if(left.x_vel < - PADDLE_SPEED)
        left.x_vel = -PADDLE_SPEED;
    if(left.y_vel > PADDLE_SPEED)
        left.y_vel = PADDLE_SPEED;
    if(left.y_vel < -PADDLE_SPEED)
        left.y_vel = -PADDLE_SPEED;
    if(left.yaw_vel > PADDLE_ROTATE_SPEED)
        left.yaw_vel = PADDLE_ROTATE_SPEED;
    if(left.yaw_vel < -PADDLE_ROTATE_SPEED)
        left.yaw_vel = -PADDLE_ROTATE_SPEED;

    if(right.x_vel > PADDLE_SPEED)
        right.x_vel = PADDLE_SPEED;
    if(right.x_vel < - PADDLE_SPEED)
        right.x_vel = -PADDLE_SPEED;
    if(right.y_vel > PADDLE_SPEED)
        right.y_vel = PADDLE_SPEED;
    if(right.y_vel < -PADDLE_SPEED)
        right.y_vel = -PADDLE_SPEED;
    if(right.yaw_vel > PADDLE_ROTATE_SPEED)
        right.yaw_vel = PADDLE_ROTATE_SPEED;
    if(right.yaw_vel < -PADDLE_ROTATE_SPEED)
        right.yaw_vel = -PADDLE_ROTATE_SPEED;
    right_paddle.set_velocity(right.x_vel,right.y_vel,right.yaw_vel);
    left_paddle.set_velocity(left.x_vel,left.y_vel,left.yaw_vel);
}

// callback function that tells OpenGL how to handle keystrokes
void keyboard( unsigned char key, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;
    cerr << "keypress: " << key << " (" << int( key ) << ") at (" << x << "," << y << ")\n";

    Velocity2D left = left_paddle.get_velocity();
    Velocity2D right = right_paddle.get_velocity();
    // process keypresses
    switch ( key )
    {
        // Escape quits program
        case EscapeKey:
            exit( 0 );
            break;

        case 'a':
        case 'A':
            left.x_vel -= PADDLE_SPEED;
            break;

        case 'd':
        case 'D':
            left.x_vel += PADDLE_SPEED;
            break;

        case 's':
        case 'S':
            left.y_vel -= PADDLE_SPEED;
            break;


        case 'w':
        case 'W':
            left.y_vel += PADDLE_SPEED;
            break;

        case 'q':
        case 'Q':
            left.yaw_vel += PADDLE_ROTATE_SPEED;
            break;

        case 'e':
        case 'E':
            left.yaw_vel -= PADDLE_ROTATE_SPEED;
            break;

            //Start or pause/resume the game on spacebar
        case ' ':
        case 'p':
        case 'P':
            if(GAMESTATE != 0)
                PAUSED = !PAUSED;
            else
                GAMESTATE = 1;
            break;

        case '+':
            BALL_WARP *=1.5;
            break;
        case '-':
            BALL_WARP /=1.5;
            break;
        case '*':
            PADDLE_WARP *= 1.5;
            break;
        case '/':
            PADDLE_WARP /=1.5;
            break;
            //Right Paddle Keys
        case '7':
            right.yaw_vel += PADDLE_ROTATE_SPEED;
            break;
        case '9':
            right.yaw_vel -= PADDLE_ROTATE_SPEED;
            break;
        case '4':
            right.x_vel -= PADDLE_SPEED;
            break;
        case '6':
            right.x_vel += PADDLE_SPEED;
            break;
        case '5':
            right.y_vel -= PADDLE_SPEED;
            break;
        case '8':
            right.y_vel += PADDLE_SPEED;
            break;
    }
    if(left.x_vel > PADDLE_SPEED)
        left.x_vel = PADDLE_SPEED;
    if(left.x_vel < - PADDLE_SPEED)
        left.x_vel = -PADDLE_SPEED;
    if(left.y_vel > PADDLE_SPEED)
        left.y_vel = PADDLE_SPEED;
    if(left.y_vel < -PADDLE_SPEED)
        left.y_vel = -PADDLE_SPEED;
    if(left.yaw_vel > PADDLE_ROTATE_SPEED)
        left.yaw_vel = PADDLE_ROTATE_SPEED;
    if(left.yaw_vel < -PADDLE_ROTATE_SPEED)
        left.yaw_vel = -PADDLE_ROTATE_SPEED;

    if(right.x_vel > PADDLE_SPEED)
        right.x_vel = PADDLE_SPEED;
    if(right.x_vel < - PADDLE_SPEED)
        right.x_vel = -PADDLE_SPEED;
    if(right.y_vel > PADDLE_SPEED)
        right.y_vel = PADDLE_SPEED;
    if(right.y_vel < -PADDLE_SPEED)
        right.y_vel = -PADDLE_SPEED;
    if(right.yaw_vel > PADDLE_ROTATE_SPEED)
        right.yaw_vel = PADDLE_ROTATE_SPEED;
    if(right.yaw_vel < -PADDLE_ROTATE_SPEED)
        right.yaw_vel = -PADDLE_ROTATE_SPEED;
    right_paddle.set_velocity(right.x_vel,right.y_vel,right.yaw_vel);
    left_paddle.set_velocity(left.x_vel,left.y_vel,left.yaw_vel);
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
