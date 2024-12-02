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

Color Material::getAmbientColor() const {
    return ambient_color;
}

Color Material::getEmitColor() const {
  return emit_color;
}

Color Material::getDifuseColor() const {
  return difus_color;
}
