#include "../include/Triangle.hpp"

Triangle::Triangle(): v0(), v1(), v2(),  materialIndex(0)
{};

Triangle::Triangle(Vector3D v0, Vector3D v1, Vector3D v2, int materialIndex): v0(v0), v1(v1), v2(v2), materialIndex(materialIndex)
{};

std::optional<Vector3D> Triangle::mollerTrumbore(const Ray &ray) const{
    //inicjalizacja wektorów i epsi(wynika z niedokładność komputera przy liczbach zmiennoprzecinkowych)
    //const float epsi = std::numeric_limits<float>::epsilon();

    const float epsi = 0.0001;
    Vector3D dest = ray.getDestination();
    Vector3D orgin = ray.getOrgin();
    Vector3D edge1 = v1.sub(v0);
    Vector3D edge2 = v2.sub(v0);
    Vector3D ray_cross_edg2 = dest.cross(edge2);
    Vector3D dist_org_v0 = orgin.sub(v0);
    Vector3D Q = dist_org_v0.cross(edge1);

    
    float det = ray_cross_edg2.dot(edge1);  //współczynnik det
    if (det > -epsi && det < epsi)
    {
        return {};
    }

    float inv_det = 1.0 / det;  //odwrotność współczynnika
    float u = inv_det * (ray_cross_edg2.dot(dist_org_v0));  //parametr u
    if((u < 0 && abs(u) > epsi) || (u > 1 && abs(u-1) > epsi))  //sprawdzenie u
    {
        return {};
    }

    float v = inv_det * (Q.dot(dest));  //współczynnik v
    if((v < 0 && abs(v) > epsi) || (u + v > 1 && abs(u + v - 1) > epsi))  //sprawdza czy punkt znajduje się w trójkącie
    {
        return {};
    }

    float dist = inv_det * (Q.dot(edge2));
    if (dist > epsi) // dystans nie jest ujemny 
    {
        return  Vector3D(orgin.add(dest.mult(dist)));
    }
    return {};
}

//zwraca Material index
int Triangle::getMaterianIndex() const {
    return materialIndex;
}

//zwraca wektor normalny do powierzchni trójkąta
Vector3D Triangle::getNormal() const {
    Vector3D edge1 = v1.sub(v0);
    Vector3D edge2 = v2.sub(v0);

    return (edge1.cross(edge2)).normalise();
}