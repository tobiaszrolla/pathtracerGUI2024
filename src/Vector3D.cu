#include "../include/Vector3D.hpp"

/*HOST_DEVICE float Vector3D::lenght() const
{
    return std::sqrt(this->posX * this->posX +
                    this->posY * this->posY +
                    this->posZ * this->posZ);
};*/

/*__host__ __device__  Vector3D::Vector3D(float x, float y, float z): posX(x), posY(y), posZ(z)
{};*/

__host__ __device__  Vector3D::Vector3D(): posX(0.0), posY(0.0), posZ(0.0)
{};

/*__host__ __device__  Vector3D Vector3D::add(const Vector3D &otherVec) const {
    return Vector3D(this->posX + otherVec.posX,  //x
                    this->posY + otherVec.posY,  //y
                    this->posZ + otherVec.posZ); //z
};*/

/*__host__ __device__ Vector3D Vector3D::sub(const Vector3D &otherVec) const {
    return Vector3D(this->posX - otherVec.posX,  //x
                    this->posY - otherVec.posY,  //y
                    this->posZ - otherVec.posZ); //z
};*/

/*__host__ __device__ Vector3D Vector3D::mult(const float &scal) const {
    return Vector3D(scal * (this->posX),scal * (this->posY),scal * (this->posZ));
};*/


__host__ __device__ float Vector3D::dot(const Vector3D &otherVec) const {
    return  this->posX * otherVec.posX +
            this->posY * otherVec.posY +
            this->posZ * otherVec.posZ;
};

/*HOST_DEVICE Vector3D Vector3D::normalise() const {
    float lenght = this->lenght();
    if(lenght == 0) {
        throw std::runtime_error("Divaid by zero during normalization");
    };
    return Vector3D(posX / lenght, 
                    posY / lenght, 
                    posZ / lenght);
};*/

Vector3D Vector3D::cross(const Vector3D &otherVec) const
{
    float newX = this->posY * otherVec.posZ - this->posZ * otherVec.posY;  //x
    float newY = this->posZ * otherVec.posX - this->posX * otherVec.posZ;  //y
    float newZ = this->posX * otherVec.posY - this->posY * otherVec.posX;  //z
    return Vector3D(newX, newY, newZ); // Zwrócenie wektora
}

float Vector3D::distanceTo(const Vector3D &otherVec) const
{
    return sqrt((this->posX - otherVec.posX) * (this->posX - otherVec.posX) +
                (this->posY - otherVec.posY) * (this->posY - otherVec.posY) +
                (this->posZ - otherVec.posZ) * (this->posZ - otherVec.posZ));
}
