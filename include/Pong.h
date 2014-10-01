/******************************************************************************
* File: Entity.cpp
* Authors: Ian Carlson, Christopher Smith
* Date: 09/16/14
* Last Modified 09/16/14
* Description: Header File that contains all the includes and global variables
* for Pong.cpp
* ****************************************************************************/

//Class include files
#include "Paddle.h"
#include "Ball.h"

// include files c/c++ libraries
#include <ctime>
#include <stdio.h>
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

//Global Class Constructs
Ball ball(Point2D(TOTAL_WIDTH/2.0,TOTAL_HEIGHT/2.0),BALL_SIZE,Color(1,0,0),Velocity2D(-500,0,0));
Paddle left_paddle(Point2D(PADDLE_WIDTH,TOTAL_HEIGHT/2.0),PADDLE_WIDTH,PADDLE_HEIGHT,Color(0,1,0));
Paddle right_paddle(Point2D(TOTAL_WIDTH - PADDLE_WIDTH, TOTAL_HEIGHT/2.0),PADDLE_WIDTH,PADDLE_HEIGHT,Color(0,1,1));

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
int SERVE_NUM = 0;
int LEFT_SCORE = 0;
int RIGHT_SCORE = 0;

// OpenGL callback function prototypes
void display( void );
void reshape( int w, int h );
void keyboard( unsigned char key, int x, int y );
void keyboardUp( unsigned char key, int x, int y);
void special_keyboard( int key, int x, int y);
void special_keyboardUp( int key, int x, int y);
void mouseclick( int button, int state, int x, int y );
void mousedrag( int x, int y );
void idle();

//Our defined functions
void showStartScreen();
void showPausedStr();
void draw_outline();
void reset_field();
void draw_scores();

// useful graphics function prototypes
void initOpenGL( void );
