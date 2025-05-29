#include "TVector.h"

//Vector defaults to x=0, y=0
TVector::TVector(float x, float y){
    this->x = x;
    this->y =y;
}

TVector TVector::add(const TVector &v)
{

    TVector temp(x + v.x, y + v.y);
    return temp;
}

TVector TVector::sub(const TVector &v)
{
    TVector temp(x - v.x, y - v.y);
    return temp;
}


TVector TVector::sProd(const TVector &v){
    TVector temp(x*v.x, y*v.y);
    return temp;
}


TVector TVector::sMul(const float &s){
    TVector temp(x*s,y*s);
    return temp;
}