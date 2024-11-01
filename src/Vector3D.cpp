#include "../include/Vector3D.h"
#include <stdexcept>

float Vector3D::lenght()
{
    return std::sqrt(this->posX * this->posX +
                    this->posY * this->posY +
                    this->posZ * this->posZ);
};

Vector3D::Vector3D(float x, float y, float z): posX(x), posY(y), posZ(z){};

Vector3D Vector3D::add(Vector3D otherVec)
{
    return Vector3D(this->posX + otherVec.posX, this->posY + otherVec.posY, this->posZ + otherVec.posZ);
};

Vector3D Vector3D::sub(Vector3D otherVec)
{
    return Vector3D(this->posX - otherVec.posX, this->posY - otherVec.posY, this->posZ - otherVec.posZ);
};

Vector3D Vector3D::mult(float scal)
{
    return Vector3D(scal * (this->posX),scal * (this->posY),scal * (this->posZ));
};

Vector3D Vector3D::cross(Vector3D otherVec)
{
    float newX = this->posY * otherVec.posZ - this->posZ * otherVec.posY;
    float newY = this->posZ * otherVec.posX - this->posX * otherVec.posZ;
    float newZ = this->posX * otherVec.posY - this->posY * otherVec.posX;
    return Vector3D(newX,newY,newY);
}

float Vector3D::dot(Vector3D otherVec)
{
    return  this->posX * otherVec.posX +
            this->posY * otherVec.posY +
            this->posZ * otherVec.posZ;
};

Vector3D Vector3D::normal()
{
    float lenght = this->lenght();
    if(lenght == 0)
    {
        throw std::runtime_error("Divaid by zero during normalization");
    };
    return Vector3D(posX/lenght, posY/lenght, posZ/lenght);
}