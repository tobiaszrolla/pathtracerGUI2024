#include "../include/Camera.hpp"

Camera::Camera(float fov, float aspectRatio,Vector3D position,float how_farX, float how_farY, float how_farZ)
{
    //origin = Vector3D(position.getX() + how_farX ,position.getY() + how_farY ,position.getZ() + how_farZ);
    //target = position;
    origin = Vector3D(0.0,-10.0,0);
    target = Vector3D(0.0,10.0,0.0);//kierunek patrzenia
    Vector3D up = Vector3D(0.0, 0.0, 1.0);//kierunek na osi Y
    Vector3D right = Vector3D(1.0, 0.0, 0.0);//kierunek na osi X

    float theta = fov * M_PI / 180.0f; // Konwersja FOV do radianów
    float h = std::tan(theta / 2.0f); // Połowa wysokości widzenia
    float viewportHeight = 2.0f * h;
    float viewportWidth = viewportHeight * aspectRatio;
    horizontal = right.mult(viewportWidth);
    vertical = up.mult(viewportHeight);
    lower_left_corner = origin
                            .sub(horizontal.mult(0.5f)) // Przesunięcie w lewo
                            .sub(vertical.mult(0.5f))   // Przesunięcie w dół
                            .add(target);               // Przesunięcie w kierunku target
}

Ray Camera::getRay(float u, float v){
    // Obliczanie punktu na płaszczyźnie widoku na podstawie współczynników (u, v)
    Vector3D pixelPosition = lower_left_corner
                                .add(horizontal.mult(u)) // Przesunięcie w poziomie
                                .add(vertical.mult(v));  // Przesunięcie w pionie
    Vector3D direction = pixelPosition.sub(origin);
    
    return Ray(origin, direction);//kierunek normalizowany przez konstruktor
}