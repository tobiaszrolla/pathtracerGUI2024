#include "../include/Triangle.hpp"

Triangle::Triangle(Vector3D v0, Vector3D v1, Vector3D v2, int materialIndex): v0(v0), v1(v1), v2(v2), materialIndex(materialIndex){};

int Triangle::mollerTrumbore(Ray ray)
{
    //inicjalizacja wektorów i epsi(wynika z niedokładność komputera przy liczbach zmiennoprzecinkowych)
    const float epsi = 0.00001;
    Vector3D dest = ray.getDestination();
    Vector3D orgi = ray.getOrgin();
    Vector3D kraw1 = v1.sub(v0);
    Vector3D kraw2 = v2.sub(v0);
    Vector3D P = dest.cross(kraw2);
    Vector3D T = orgi.sub(v0);
    Vector3D Q = T.cross(kraw1);

    //współczynnik a
    float a = 1.0f/(P.dot(kraw1));

    //Porównania dystanns współcznynniki
    float u = a*P.dot(T);
    if(fabs(u) < epsi || u > 1)
    {
        return -1;
    }
    float v = a*Q.dot(dest);
    if(fabs(v) < epsi || (u + v) > 1)
    {
        return -1;
    }
    float dist = a * Q.dot(kraw2);
    if (dist < 0.0f)
    {
        return -1;
    }
    return materialIndex;
}