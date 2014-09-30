/******************************************************************************
* File: Pong.cpp
* Authors: Ian Carlson, Christopher Smith
* Description: Pong game implementation
* ****************************************************************************/
#include "../include/Pong.h"

/******************************************************************************
* Function: main( int argc, char *argv[] )
* Authors: Ian Carlson, Christopher Smith
* Description: Start of the Pong game that creates the limits for all objects
* ****************************************************************************/

int main( int argc, char *argv[] )
{
    //limits for all game objects so they stay on screen
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

/******************************************************************************
* Function: Entity2D( Point2D point, Velocity2D vel )
* Authors: Ian Carlson, Christopher Smith
* Note: Function based off of a template from Dr. Weiss
* Description: initializes glut handles for keyboard and window size
* ****************************************************************************/
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
    glutIdleFunc( idle );
}

/******************************************************************************/
/*                          OpenGL callback functions                         */
/******************************************************************************/

// callback function that tells OpenGL how to redraw window
void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    // clear the display
    switch(GAMESTATE)
    {
    //Game not yet started
    case 0:
        showStartScreen();
        LEFT_SCORE = 0;
        RIGHT_SCORE = 0;
        //Display Name
        //Display Controls
        break;

    }
    if(PAUSED)
    {
        showPausedStr();
    }
    draw_scores();
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
    glEnable( GL_LINE_STIPPLE );
    glLineStipple( 1, 0xFF00 );
    glBegin(GL_LINES);

    glVertex2f(TOTAL_WIDTH*.5, TOP_COURT_EDGE);
    glVertex2f(TOTAL_WIDTH*.5, BOTTOM_COURT_EDGE);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
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
        switch (ball.goal_made())
        {
        case 1:
            RIGHT_SCORE++;
            SERVE_NUM++;
            reset_field();
            if( RIGHT_SCORE == 10 )
                GAMESTATE = 0;
            break;
        case 2:
            LEFT_SCORE++;
            SERVE_NUM++;
            reset_field();
            if( LEFT_SCORE == 10 )
                GAMESTATE = 0;
            break;
        default:
            left_paddle.animate(scale_factor*PADDLE_WARP);
            if(ball.check_paddle_collision( left_paddle , scale_factor*BALL_WARP, scale_factor*PADDLE_WARP))
                left_paddle.shrink();
            right_paddle.animate(scale_factor*PADDLE_WARP);
            if(ball.check_paddle_collision( right_paddle , scale_factor*BALL_WARP, scale_factor*PADDLE_WARP))
                right_paddle.shrink();
            break;
        }
    }
    last_time = new_time;
    glutPostRedisplay();
}

void draw_scores()
{
    char left_str[10];
    char right_str[10];
    sprintf(left_str,"%d",LEFT_SCORE);
    sprintf(right_str,"%d",RIGHT_SCORE);
    glColor3f(0,1,0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(200,1400,0);
    glScalef(0.6,0.6,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)"Player 1");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,1300,0);
    glScalef(0.6,0.6,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)left_str);
    glPopMatrix();

    glColor3f(0,1,1);
    glPushMatrix();
    glTranslatef(800,1400,0);
    glScalef(0.6,0.6,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)"Player 2");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(800,1300,0);
    glScalef(0.6,0.6,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)right_str);
    glPopMatrix();
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

void reset_field()
{
    left_paddle.set_size(PADDLE_WIDTH,PADDLE_HEIGHT);
    left_paddle.move2D(PADDLE_WIDTH,TOTAL_HEIGHT/2.0,0);
    right_paddle.set_size(PADDLE_WIDTH,PADDLE_HEIGHT);
    right_paddle.move2D(TOTAL_WIDTH-PADDLE_WIDTH,TOTAL_HEIGHT/2.0,0);

    ball.move2D( TOTAL_WIDTH/2.0, TOTAL_WIDTH/2.0, 0);

    if(SERVE_NUM % 2 == 0)
        ball.set_velocity(-500,0,0);
    else
        ball.set_velocity(500,0,0);
}
