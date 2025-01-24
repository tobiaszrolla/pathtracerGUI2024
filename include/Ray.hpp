#include "Vector3D.hpp"
#pragma once
#ifdef __CUDACC__
    #define DEVICE __device__
#else
    #define DEVICE
#endif
//==============================================Promien=================================================================//
//klasa sklada sie z 2 wektorow3D//
class Ray
{
    private:
        Vector3D orgin;
        Vector3D destination;
    public:
        //konstruktory
        DEVICE Ray();
        DEVICE Ray(Vector3D org, Vector3D des): orgin(org), destination(des.normalise()){};  //generacja kierunek znormalizowany

        //other
        DEVICE Vector3D getOrgin() const  //zwraca źródło promienia
        {
            return orgin;
        }
        DEVICE Vector3D getDestination() const  //zwraca kierunek promienia
        {
            return destination;
        }

};