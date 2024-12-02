#include "Light.hpp"
class TraceRay
{
    protected:
        Color traceRay( Ray &ray, 
                        int depth, 
                        const std::vector<Triangle> &triangles, 
                        const std::vector<Material> &materiales, 
                        const Light& light) const;
        bool isInShadow( Vector3D point,  Vector3D& lightDir, const std::vector<Triangle>& triangles) const;
};