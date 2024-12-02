#include "Vector3D.hpp"
#include <algorithm>

//==============================================Color=================================================================//
//potomek Wektora 3D//
//przechowuje zmienno przecinkowe kolory//
//konwertuje je na format PPM
//!!! W OBRĘBIE KLASY UŻYWAMY posX, posY, posZ ZAMIAST R, G, B !!!//

class Color : public Vector3D
{
    private:

    public:
        //konstruktor
        Color(float r = 0.0f, float g = 0.0f, float b = 0.0f)
        : Vector3D(r, g, b) {}

        //gettery
        float getR();
        float getG();
        float getB();

        //inne
        void clamp();
        Color& operator=(const Vector3D &vec);
        void toPPM(int &r, int &g, int &b);
        Color add(const Color &otherColor) const;


};