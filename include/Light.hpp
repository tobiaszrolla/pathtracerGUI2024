#include "Camera.hpp"
#include "Vector3D.hpp"

//==============================================Color=================================================================//
//reprezentuje źródło oświetlenia na scenie

class Light {
private:
    Vector3D position; 
    Color color;        
    float intensity; 
public:   
    
    __host__ __device__ Light(Vector3D p, Color c, float i) : position(p), color(c), intensity(i) {}
    __device__ Vector3D getPosition() const {return position;}
    __device__ Color getColor() const {return color;}
    __device__ float getIntensity() const {return intensity;}
};