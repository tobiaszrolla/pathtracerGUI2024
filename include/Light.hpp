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
    
    Light(Vector3D p, Color c, float i) : position(p), color(c), intensity(i) {}
    Vector3D getPosition() const {return position;}
    Color getColor() const {return color;}
    float getIntensity() const {return intensity;}
};