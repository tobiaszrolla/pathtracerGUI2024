#include "Ray.hpp"
#include "Material.hpp"
#include "Vector3D.hpp"
#include <optional>

//==============================================Trójkąt=================================================================//
//klasa zawiera informacje o wierzchołkach//
//przechowuje index materiału//
//obsługuje przecięcia//

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
        std::optional<Vector3D> mollerTrumbore(const Ray &ray) const;
        int getMaterianIndex() const;
        Vector3D getNormal() const;
};