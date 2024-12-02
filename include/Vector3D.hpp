#include <math.h>
#include <stdexcept>
#pragma once

//==============================Klasa odpowiednik wektora w przestrzeni===========================================================//
class Vector3D
{
    protected:
        float posX;
        float posY;
        float posZ;
    private:
        float lenght() const;
    public:
        //constructors
        Vector3D();
        Vector3D(float x, float y, float z);
        //getter
        float getX()const{return posX;};
        float getY()const{return posY;};
        float getZ()const{return posZ;};
        //other
        Vector3D add(const Vector3D &otherVec) const;
        Vector3D sub(const Vector3D &otherVec) const;
        Vector3D mult(const float &scal) const;
        Vector3D cross(const Vector3D &otherVec) const;//iloczyn wyektorowy z ang cross product
        float dot(const Vector3D &otherVec) const; //iloczyn skalarny z ang dot product
        Vector3D normalise() const;

};
