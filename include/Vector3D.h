#include <math.h>
#pragma once

//==============================Klasa odpowiednik wektora w przestrzeni===========================================================//
class Vector3D
{
    private:
        float posX;
        float posY;
        float posZ;
    private:
        float lenght();
    public:
        Vector3D(float x, float y, float z);
        Vector3D add(Vector3D otherVec);
        Vector3D sub(Vector3D otherVec);
        Vector3D mult(float scal);
        Vector3D cross(Vector3D otherVec);//iloczyn wyektorowy z ang cross product
        float dot(Vector3D otherVec); //iloczyn skalarny z ang dot product
        Vector3D normal();




};