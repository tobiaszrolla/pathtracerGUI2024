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
        HOST_DEVICE Color(float r = 0.0f, float g = 0.0f, float b = 0.0f)
        : Vector3D(r, g, b) {}

        //gettery
        float getR();
        float getG();
        float getB();

        //inne
        void clamp();
        DEVICE Color& operator=(const Vector3D &vec);
        void toPPM(int &r, int &g, int &b);
        DEVICE Color add(const Color &otherColor) const;
        // Mnożenie przez drugi kolor
        DEVICE Color multColor(const Color &otherColor) const {
            return Color(this->posX * otherColor.getX(),  //R
                        this->posY * otherColor.getY(),  //G
                        this->posZ + otherColor.getZ()); //B
        }


};