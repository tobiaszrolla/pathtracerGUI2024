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
        __host__ __device__ Camera(float fov, float aspectRatio, Vector3D max_positon, float how_far, float how_farY, float how_farZ);//kąt widzenia stosunek wysokości i szerokości obrazu
        //__host__ __device__ Ray getRay(float u, float v);
        __host__ __device__ Vector3D getOrigin() const;
        __device__ Ray getRay(float u, float v){
        // Obliczanie punktu na płaszczyźnie widoku na podstawie współczynników (u, v)
        Vector3D pixelPosition = lower_left_corner
                                    .add(horizontal.mult(u)) // Przesunięcie w poziomie
                                    .add(vertical.mult(v));  // Przesunięcie w pionie
        Vector3D direction = pixelPosition.sub(origin);
    
        return Ray(origin, direction);//kierunek normalizowany przez konstruktor
    }

};