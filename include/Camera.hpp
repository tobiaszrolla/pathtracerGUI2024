#include "Mesh.hpp"
#include <random>

class Camera
{
    private:
        Vector3D origin;
        Vector3D target;
        Vector3D horizontal;// Wektor poziomy
        Vector3D vertical;// Wektor pionowy
        Vector3D lower_left_corner;
    private:

    public:
        Camera(float fov, float aspectRatio, Vector3D max_positon, float how_far, float how_farY, float how_farZ);//kąt widzenia stosunek wysokości i szerokości obrazu
        Ray getRay(float u, float v);

};