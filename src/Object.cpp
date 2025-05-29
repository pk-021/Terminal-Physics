#include "Object.h"
#include "cmath"

Object::Object(Shape *s, int mass)
{
    this->shape = s;
    this->mass = mass; // one pixel = 1kg
    this->x = s->x;    // one pixel = 1m
    this->y = s->y;    // one pixel = 1m
}

// set the velocity of the object
void Object::setVelocity(TVector v)
{
    velocity.x = v.x; // m per s i.e pixels/s
    velocity.y = v.y; //
}

// apply force for framerate time
void Object::applyForce(TVector v, float time)
{

    TVector acc = v.sMul(1.0f / mass);
    this->velocity = this->velocity.add(acc.sMul(time));

    // std::cout << "applyForce -> acceleration: (" << acc.x << ", " << acc.y << "), ";
    // std::cout << "velocity after applyForce: (" << velocity.x << ", " << velocity.y << ")" << std::endl;
}

// update the position for unit time based on current velocity
void Object::update(float deltaTime)
{
    this->x += velocity.x * deltaTime;
    this->y += velocity.y * deltaTime;

    // handle horizontal collision with wall
    if (this->x <= shape->win->xMin)
    {
        this->x = shape->win->xMin;
        velocity.x *= -1;
        // std::cout<<"Horizontal collision left"<<std::endl;
    }
    if (this->x >= (shape->xMax))
    {
        this->x = shape->xMax;
        velocity.x *= -1;
        // std::cout<<"Horizontal collision right"<<std::endl;
    }

    // handle vertical collision with wall
    if (this->y <= shape->win->yMin)
    {
        this->y = shape->win->yMin;
        velocity.y *= -1;
        // std::cout<<"Vertical collision roof"<<std::endl;
    }
    if (this->y >= shape->yMax)
    {
        this->y = shape->yMax;
        velocity.y *= -1;
        // std::cout<<"Vertical collision floor"<<std::endl;
    }
    std::cout << "xMax: " << shape->win->xMax << ", yMax: " << shape->win->yMax << std::endl;
    std::cout << "Position: (" << this->x << ", " << this->y << ")" << std::endl;
    std::cout << "Velocity: (" << velocity.x << ", " << velocity.y << ")" << std::endl;

    shape->move(round(this->x), round(this->y), true);
}

// move the physical obj as well as the shape
void Object::move(float x, float y)
{
    this->x = x;
    this->y = y;
    shape->move(std::round(x), std::round(y), false);
}