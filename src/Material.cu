#include "../include/Material.hpp"
Material::Material()
        : ambient_color(0.0f,  0.0f,  0.0f),
          difus_color(0.0f,  0.0f,  0.0f), 
            secul_color(0.0f,  0.0f,  0.0f),
              emit_color(0.0f, 0.0f, 0.0f), 
              transp(1.0f), 
            shines(0.0f), 
          lightModel(2),
        refraction(1.0f) 
{}

__device__ Color Material::getAmbientColor() const {
    return ambient_color;
}

__device__ Color Material::getEmitColor() const {
  return emit_color;
}

__device__ Color Material::getDifuseColor() const {
  return difus_color;
}
__device__ Color Material::getSpectularColor() const {
  return secul_color;
}
__device__ int Material::getLightModel() const {
  return lightModel;
}

