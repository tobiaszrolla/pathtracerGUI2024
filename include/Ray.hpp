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
        //konstruktory
        Ray();
        Ray(Vector3D org, Vector3D des): orgin(org), destination(des.normalise()){};  //generacja kierunek znormalizowany

        //other
        Vector3D getOrgin() const  //zwraca źródło promienia
        {
            return orgin;
        }
        Vector3D getDestination() const  //zwraca kierunek promienia
        {
            return destination;
        }

};