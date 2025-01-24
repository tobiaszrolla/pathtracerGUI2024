#include "Ray.hpp"
#include "Material.hpp"
#include "Vector3D.hpp"
#include <optional>

#ifdef __CUDACC__
    #define DEVICE __device__
#else
    #define DEVICE
#endif

//==============================================Trójkąt=================================================================//
//klasa zawiera informacje o wierzchołkach//
//przechowuje index materiału//
//obsługuje przecięcia//
struct OptionalGPU
{
    bool option;
    Vector3D vector;
};
class Triangle
{
    private:
        Vector3D v0;
        Vector3D v1;
        Vector3D v2;
        int materialIndex;  //słóży do przeszukania listy materiałów
    public:
        Triangle();
        Triangle(Vector3D v0, Vector3D v1, Vector3D v2, int materialIndex);
        DEVICE OptionalGPU mollerTrumbore(const Ray &ray) const;
        DEVICE int getMaterialIndex() const;
        DEVICE Vector3D getNormal() const;
        Vector3D center() const;
};