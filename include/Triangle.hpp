// information about vertices and matirial in one place
#include "Ray.hpp"
#include "Vector3D.hpp"
struct Material
{
    Vector3D ambientColor;
    Vector3D difusColor;
    Vector3D seculColor;
    Vector3D emitColor;
    float transp;
    float shines;
    float refraction;
    int lightModel;

    Material()
        : ambientColor(0.0f, 0.0f, 0.0f), difusColor(0.0f, 0.0f, 0.0f),
          seculColor(0.0f, 0.0f, 0.0f),emitColor(0.0f,0.0f,0.0f), transp(1.0f), shines(0.0f), lightModel(2),refraction(1.0f) {}
};
class Triangle
{
    private:
        Vector3D v0;
        Vector3D v1;
        Vector3D v2;
        int materialIndex;
    public:
        Triangle(Vector3D v0, Vector3D v1, Vector3D v2, int materialIndex);
        int mollerTrumbore(Ray ray);
};