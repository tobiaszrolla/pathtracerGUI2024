#include "../include/TraceRay.hpp"

bool TraceRay::isInShadow( Vector3D point,  Vector3D& lightDir, const std::vector<Triangle>& triangles) const{
    Ray shadowRay(point.add(lightDir.mult(0.001)), lightDir); // Unikaj samo-przecięcia
    for (const Triangle& triangle : triangles) {
        if (triangle.mollerTrumbore(shadowRay)) {
            return true; // Punkt znajduje się w cieniu
        }
    }
    return false; // Punkt nie jest w cieniu
}

Color TraceRay::traceRay(Ray &ray, 
                        int depth, 
                        const std::vector<Triangle> &triangles, 
                        const std::vector<Material> &materiales, 
                        const Light& light) const
{
    if(depth <= 0)
    {
        return Color(0.0, 0.0, 0.0);
    }
    for(const Triangle &triangle : triangles)
    {
        std::optional<Vector3D> insertion = triangle.mollerTrumbore(ray);
        if(insertion)
        {
            Vector3D point = *insertion;
            int mat_inx = triangle.getMaterianIndex();
            Vector3D lightDir = light.getPosition().sub(point).normalise();//kierunek światła


            bool in_shadow = isInShadow(point, lightDir, triangles);
            if(!in_shadow){ 

                //Zbieramy kolorki
                Color ambient_color = materiales[mat_inx].getAmbientColor();
                Color emit_color = materiales[mat_inx].getEmitColor();
                Color diffus_color = materiales[mat_inx].getDifuseColor();

                Vector3D tri_normal = triangle.getNormal(); // Normalny wektor do trójkąta
                float diffus_parameter = std::max(tri_normal.dot(lightDir), 0.0f); 

                diffus_color = diffus_color.mult(diffus_parameter).mult(light.getIntensity());

                return ambient_color
                            .add(diffus_color)
                            .add(emit_color);
            }
            
        }
    }
    return Color(0.0,0.0,0.0);
};