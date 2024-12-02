#include "../include/Color.hpp"

void Color::clamp(){
    posX = std::clamp(posX, 0.0f, 1.0f);
    posY = std::clamp(posY, 0.0f, 1.0f);
    posZ = std::clamp(posZ, 0.0f, 1.0f);
}

float Color::getR(){
    return posX;
};

float Color::getG(){
    return posY;
};

float Color::getB(){
    return posZ;
};


Color& Color::operator=(const Vector3D& vec) {
        // Przypisujemy wartości posX, posY, posZ
        this->posX = vec.getX();
        this->posY = vec.getY();
        this->posZ = vec.getZ();
        return *this;  // Zwracamy referencję do obiektu, aby umożliwić łańcuchowe przypisania
    }

void Color::toPPM(int& r, int& g, int& b){
        r = static_cast<int>(std::clamp(getR() * 255.0f, 0.0f, 255.0f));
        g = static_cast<int>(std::clamp(getG() * 255.0f, 0.0f, 255.0f));
        b = static_cast<int>(std::clamp(getB() * 255.0f, 0.0f, 255.0f));
    }

Color Color::add(const Color &otherColor) const{
    return Color(this->posX + otherColor.posX,  //R
                 this->posY + otherColor.posY,  //G
                 this->posZ + otherColor.posZ); //B
}