/******************************************************************************
 * File: Entity.h
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Header file for the Entity class, the parent of all
 * drawable objects for our programs. 
 * ***************************************************************************/

class Entity
{
    //Virtual Functions
    virtual void draw() = 0;

    //Functions
    public:
    Entity(float x, float y, float z, float roll, float pitch, float yaw);
    ~Entity();

    float get_x();
    float get_y();
    float get_z();
    float get_yaw();
    float get_pitch();
    float get_roll();
    void set_x(float x);
    void set_y(float y);
    void set_z(float z);
    void set_yaw(float yaw);
    void set_pitch(float pitch);
    void set_roll(float roll);

    //Variables
    private:
    float x;
    float y;
    float z;
    float yaw;
    float pitch;
    float roll;
};
