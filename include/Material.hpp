#include "Color.hpp"

#ifdef __CUDACC__
    #define DEVICE __device__
#else
    #define DEVICE
#endif
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
        DEVICE Color getAmbientColor() const;
        DEVICE Color getEmitColor() const;
        DEVICE Color getDifuseColor() const;
        DEVICE Color getSpectularColor() const;
        DEVICE int getLightModel() const;
};