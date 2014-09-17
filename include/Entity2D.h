
/******************************************************************************
 * File: Entity2D.h
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Header file for the Entity2D class, the parent of all
 * drawable objects for our programs. 
 * ***************************************************************************/

class Entity2D
{
    //Virtual Functions
    virtual void draw() = 0;

    //Functions
    public:
    Entity2D(float x = 0, float y = 0, float yaw = 0);
    ~Entity2D();

    //Getters
    float get_x();
    float get_y();
    float get_yaw();

    //Setters
    void set_x(float x);
    void set_y(float y);
    void set_yaw(float yaw);

    //Movement
    void translate2D(float x, float y);
    void rotate2D(float yaw);
    void move2D(float x, float y, float yaw);

    private:

    //Variables
    public:
    
    private:
    float x;
    float y;
    float yaw;
}