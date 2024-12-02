#include "Color.hpp"

//==============================================Materiał=================================================================//
//kontener na różne kolory i inne właśniwości materiału//

class Material
{
    public:
        Color ambient_color;
        Color difus_color;
        Color secul_color;
        Color emit_color;
        float transp;
        float shines;
        float refraction;
        int lightModel;
    public:
        Material();
        Color getAmbientColor() const;
        Color getEmitColor() const;
        Color getDifuseColor() const;
};