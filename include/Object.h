#ifndef OBJECT_H
#define OBJECT_H
#include "Shape.h"
#include "TVector.h"

class Object
{
private:
public:
    Object(Shape *s, int m);
    int mass;
    float x;
    float y;


    Shape *shape;
    TVector velocity;
    TVector acceleration;
    void applyForce(TVector v, float time);
    void setVelocity(TVector v);
    void update(float deltaTime);
    void move(float x, float y);
};

#endif