#include <math.h>
#include <stdexcept>
#pragma once
#ifdef __CUDACC__
    #define HOST_DEVICE __host__ __device__
    #define DEVICE __device__
#else
    #define HOST_DEVICE
    #define DEVICE
#endif
//==============================Klasa odpowiednik wektora w przestrzeni===========================================================//
class Vector3D
{
    protected:
        float posX;
        float posY;
        float posZ;
    private:
        //HOST_DEVICE float lenght() const;
        HOST_DEVICE float lenght() const {
            return sqrtf(this->posX * this->posX +
                        this->posY * this->posY +
                        this->posZ * this->posZ);
            };
    public:
        //constructors
        HOST_DEVICE Vector3D();
        //HOST_DEVICE Vector3D(float x, float y, float z);
        HOST_DEVICE Vector3D(float x, float y, float z): posX(x), posY(y), posZ(z) {};
        //getter
        HOST_DEVICE float getX()const{return posX;};
        HOST_DEVICE float getY()const{return posY;};
        HOST_DEVICE float getZ()const{return posZ;};
        //other
        //HOST_DEVICE Vector3D add(const Vector3D &otherVec) const;
        HOST_DEVICE  Vector3D add(const Vector3D &otherVec) const {
        return Vector3D(this->posX + otherVec.posX,  //x
                    this->posY + otherVec.posY,  //y
                    this->posZ + otherVec.posZ); //z
        };
        //HOST_DEVICE Vector3D sub(const Vector3D &otherVec) const;
        HOST_DEVICE Vector3D sub(const Vector3D &otherVec) const {
        return Vector3D(this->posX - otherVec.posX,  //x
                    this->posY - otherVec.posY,  //y
                    this->posZ - otherVec.posZ); //z
        };
        //HOST_DEVICE Vector3D mult(const float &scal) const;
        HOST_DEVICE Vector3D mult(const float &scal) const {
            return Vector3D(scal * (this->posX),scal * (this->posY),scal * (this->posZ));
        };
        HOST_DEVICE Vector3D cross(const Vector3D &otherVec) const;//iloczyn wyektorowy z ang cross product
        HOST_DEVICE float dot(const Vector3D &otherVec) const; //iloczyn skalarny z ang dot product
        //HOST_DEVICE Vector3D normalise() const;
        HOST_DEVICE Vector3D normalise() const {
                float len = this->lenght();
            if (len > 0.00001f) { // Bezpieczny zakres, aby uniknąć dzielenia przez bardzo małe wartości
                return Vector3D(posX / len, posY / len, posZ / len);
            }
            // Jeśli długość jest niemal zerowa, zwracamy wektor zerowy
            return Vector3D(0.0f, 0.0f, 0.0f);
        };
        float distanceTo(const Vector3D &otherVec) const;

};
