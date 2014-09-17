/******************************************************************************
 * File: Entity3D.h
 * Authors: Ian Carlson, Christopher Smith
 * Date: 09/16/14
 * Last Modified: 09/16/14
 * Description: Header file for the Entity3D class, the parent of all 
 * 3D drawable objects for our programs. 
 * ***************************************************************************/

class Entity3D
{
    //Virtual Functions
    virtual void draw() = 0;

    //Functions
    public:
    Entity3D(float x, float y, float z, float roll, float pitch, float yaw);
    ~Entity();

    //Getters
    float get_z();
    float get_pitch();
    float get_roll();

    //Setters
    void set_z(float z);
    void set_pitch(float pitch);
    void set_roll(float roll);

    //Movers
    void translate3D(float x, float y, float z);
    void rotate3D(float roll, float pitch, float yaw);
    void move3D(float x, float y, float z, float roll, float pitch, float yaw);

    //Variables
    private:
    float z;
    float pitch;
    float roll;
};
