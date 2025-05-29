#ifndef TVECTOR_H
#define TVECTOR_H

class TVector
{
private:

public:
    float x;
    float y;
    
    TVector(float x =0, float y =0);

    TVector add(const TVector &v);
    TVector sub(const TVector &v);
    TVector sProd(const TVector &v);
    TVector sMul(const float &s);

};

#endif