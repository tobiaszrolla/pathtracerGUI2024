#include "Vector3D.hpp"
#pragma once

//==============================================Promien=================================================================//
//klasa sklada sie z 2 wektorow3D//
class Ray
{
    private:
        Vector3D orgin;
        Vector3D destination;
    public:
        Ray();
        Ray(Vector3D org, Vector3D des): orgin(org), destination(des){};
        Vector3D getOrgin()
        {
            return orgin;
        }
        Vector3D getDestination()
        {
            return destination;
        }

};