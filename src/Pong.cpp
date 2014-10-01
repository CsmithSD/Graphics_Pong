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

/******************************************************************************
* Function: display( )
* Authors: Ian Carlson, Christopher Smith
* Description: Displays the game based on the state of it
* ****************************************************************************/
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
        BALL_WARP = 1;
        PADDLE_WARP = 1;
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

/******************************************************************************
* Function: draw_outline()
* Authors: Ian Carlson, Christopher Smith
* Description: Draws the outline for the court boundraies and the half court line
* ****************************************************************************/
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

    //Half court line
    glLineStipple( 1, 0xFF00 );
    glBegin(GL_LINES);

    glVertex2f(TOTAL_WIDTH*.5, TOP_COURT_EDGE);
    glVertex2f(TOTAL_WIDTH*.5, BOTTOM_COURT_EDGE);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

/******************************************************************************
* Function: idle()
* Authors: Ian Carlson, Christopher Smith
* Description: Animates all the playing objects
* ****************************************************************************/
void idle()
{
    //We want the screen to update as quickly as possible, but
    //scale the motion to the amount of time between frames.
    //We define "Normal" as 25 frames per second and scale based on that
    static clock_t last_time = clock();
    static clock_t last_right_shrink =  clock() - 10000;
    static clock_t last_left_shrink  =  clock() - 10000;
    clock_t new_time = clock();
    clock_t delta = new_time - last_time;
    float scale_factor = ((float)delta/CLOCKS_PER_SEC)/(0.04);

    if(GAMESTATE == 1 && !PAUSED)
    {
        ball.animate(scale_factor*BALL_WARP);
        switch (ball.goal_made())
        {
        //if the right player scores
        case 1:
            RIGHT_SCORE++;
            SERVE_NUM++;
            reset_field();
            if( RIGHT_SCORE == 10 )
                GAMESTATE = 0;
            break;
        //if the left player scores
        case 2:
            LEFT_SCORE++;
            SERVE_NUM++;
            reset_field();
            if( LEFT_SCORE == 10 )
                GAMESTATE = 0;
            break;
        //if no one scores during the ball's animate call the paddles move and then collision is checked
        default:
            left_paddle.animate(scale_factor*PADDLE_WARP);
            //Shrinks the paddle by 10% if the ball strikes it
            if(ball.check_paddle_collision( left_paddle , scale_factor*BALL_WARP, scale_factor*PADDLE_WARP) && ((clock() - last_left_shrink) > 10000) )
            {
                left_paddle.shrink();
                last_left_shrink = clock();
            }
            right_paddle.animate(scale_factor*PADDLE_WARP);
            if(ball.check_paddle_collision( right_paddle , scale_factor*BALL_WARP, scale_factor*PADDLE_WARP) && ((clock() - last_right_shrink) > 10000) )
            {
                right_paddle.shrink();
                last_right_shrink = clock();
            }
            break;
        }
    }
    last_time = new_time;
    glutPostRedisplay();
}

/******************************************************************************
* Function: draw_scores()
* Authors: Ian Carlson, Christopher Smith
* Description: Displays the scores to the screen
* ****************************************************************************/
void draw_scores()
{
    char left_str[10];
    char right_str[10];
    sprintf(left_str,"%d",LEFT_SCORE);
    sprintf(right_str,"%d",RIGHT_SCORE);

    //Displays the Player 1 string to the screen
    glColor3f(0,1,0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(200,1400,0);
    glScalef(0.6,0.6,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)"Player 1");
    glPopMatrix();

    //Displays the Player 1 score to the screen
    glPushMatrix();
    glTranslatef(200,1300,0);
    glScalef(0.6,0.6,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)left_str);
    glPopMatrix();

    //Displays the Player 2 string to the screen
    glColor3f(0,1,1);
    glPushMatrix();
    glTranslatef(900,1400,0);
    glScalef(0.6,0.6,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)"Player 2");
    glPopMatrix();

    //Displays the Player 2 score to the screen
    glPushMatrix();
    glTranslatef(900,1300,0);
    glScalef(0.6,0.6,1);
    glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)right_str);
    glPopMatrix();
}

/******************************************************************************
* Function: showPausedStr()
* Authors: Ian Carlson, Christopher Smith
* Description: Displays that the game is paused when paused
* ****************************************************************************/
void showPausedStr()
{
    glColor3f(1,1,1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef( 350, 100, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"***PAUSED***" );
    glPopMatrix();
}

/******************************************************************************
* Function: showStartScreen()
* Authors: Ian Carlson, Christopher Smith
* Description: Displays the start screen for controls of game
* ****************************************************************************/
void showStartScreen()
{
    //Displays player 1 Controls
    glColor3f(1,1,1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef( 100, 1150, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"PLAYER 1 CONTROLS:" );
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 150, 950, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"W,w: Move Up" );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 150, 800, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"D,d: Move Down" );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 150, 650, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"A,a: Move Left" );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 150, 500, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"D,d: Move Right" );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 150, 350, 0 );


    //Displays the universal controls for speeds and pause
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"Q, q & E, e: Rotate Left/Right" );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 500, 250, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"Spacebar, p, P: Pause Start Game" );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 500, 150, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"+, -: Speed Up/Slow Ball" );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 500, 50, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"*, /: Speed Up/Slow Paddles" );
    glPopMatrix();


    //Displays the Controls for Player 2
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef( 900, 1150, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"PLAYER 2 CONTROLS:" );
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 940, 950, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"Up Arrow, 8: Move Up" );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 940, 800, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"Down Arrow, 5, 2: Move Down" );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 940, 650, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"Left Arrow, 4: Move Left" );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 940, 500, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"Right Arrow, 6: Move Right" );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 940, 350, 0 );
    // while ( *string ) glutStrokeCharacter( GLUT_STROKE_ROMAN, *string++ );
    glScalef(0.3,0.3,1);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)"7, Home & 9, PgUp: Rotate Left/Right" );
    glPopMatrix();
    glPushMatrix();




}

/******************************************************************************
* Function: reshape( int w, int h)
* Authors: Ian Carlson, Christopher Smith
* Description: Resizes the screen
* Arguments:
    w: width of the screen
    h: height of the screen
* ****************************************************************************/
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

/******************************************************************************
* Function: special_keyboard( int key, int x, int y )
* Authors: Ian Carlson, Christopher Smith
* Description: Handles the numpad and arrow keys for moving right paddle
* Arguments:
*   key: code of the key that was pressed
*   x: x coordinate the key was pressed at
*   y: y coordinate the key was pressed at
* ****************************************************************************/
void special_keyboard( int key, int x, int y)
{
    y = ScreenHeight -y;
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

/******************************************************************************
* Function: special_keyboardUp( int key, int x, int y )
* Authors: Ian Carlson, Christopher Smith
* Description: Handles the numpad and arrow keys for moving right paddle on release
* Arguments:
*   key: code of the key that was released
*   x: x coordinate the key was released at
*   y: y coordinate the key was released at
* ****************************************************************************/
void special_keyboardUp( int key, int x, int y)
{
    y = ScreenHeight -y;
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

/******************************************************************************
* Function: keyboardUp( unsigned char key, int x, int y )
* Authors: Ian Carlson, Christopher Smith
* Description: Handles the regular keys
* Arguments:
*   key: code of the key that was pressed
*   x: x coordinate the key was pressed at
*   y: y coordinate the key was pressed at
* ****************************************************************************/
void keyboardUp(unsigned char key, int x, int y)
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;
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
    case '2':
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
/******************************************************************************
* Function: keyboard( unsigned chart key, int x, int y )
* Authors: Ian Carlson, Christopher Smith
* Description: Handles the normal key presses for pong
* Arguments:
*   key: code of the key that was pressed
*   x: x coordinate the key was pressed at
*   y: y coordinate the key was pressed at
* ****************************************************************************/

// callback function that tells OpenGL how to handle keystrokes
void keyboard( unsigned char key, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;
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
    case '=':
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
    case '2':
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


/******************************************************************************
* Function: reset_field()
* Authors: Ian Carlson, Christopher Smith
* Description: Resets the game back to start if a goal is scored.
* ****************************************************************************/
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
