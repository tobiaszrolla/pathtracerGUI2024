#include "../include/TraceRay.hpp"

__device__ bool TraceRay::isInShadow(Vector3D point, Vector3D& lightDir, Triangle* triangles, int numTriangles) {
    Ray shadowRay(point.add(lightDir.mult(0.00001)), lightDir); // Unikaj samo-przecięcia
    for (int i = 0; i < numTriangles; ++i) {
        if (triangles[i].mollerTrumbore(shadowRay).option) {
            return true; // Punkt znajduje się w cieniu
        }
    }
    return false; // Punkt nie jest w cieniu
}

__device__ Color TraceRay::traceRay(Ray& ray, 
                                    int depth, 
                                    Triangle* triangles, 
                                    Material* materials, 
                                    int numTriangles, 
                                    Light light,
                                    Color prev_color = Color(0.0, 0.0, 0.0)) {
    if (depth <= 0) {
        return Color(0.0, 0.0, 0.0);
    }
    for (int i = 0; i < numTriangles; ++i) {
        OptionalGPU insertion = triangles[i].mollerTrumbore(ray);
        if (insertion.option) {
            Vector3D point = insertion.vector;
            int mat_inx = triangles[i].getMaterialIndex();
            Vector3D lightDir = light.getPosition().sub(point).normalise();

            bool in_shadow = isInShadow(point, lightDir, triangles, numTriangles);
            if (!in_shadow) {
                Color ambientColor = materials[mat_inx].getAmbientColor();
                Color emitColor = materials[mat_inx].getEmitColor();
                Color diffusColor = materials[mat_inx].getDifuseColor();

                Vector3D triNormal = triangles[i].getNormal();
                float diffuseParameter = fmaxf(triNormal.dot(lightDir), 0.0f);
                diffusColor = diffusColor.mult(diffuseParameter).mult(light.getIntensity());

                Color reflectionColor(0.0, 0.0, 0.0);
                
                if (materials[mat_inx].lightModel >= 2) {
                    // Obliczanie odbicia
                    Vector3D reflectionDir = lightDir.sub(triNormal.mult(2 * lightDir.dot(triNormal)));
                    reflectionDir = reflectionDir.normalise();

                    Ray reflectionRay(point.add(reflectionDir.mult(0.0001)), reflectionDir);
                    int new_depth = depth - 1;
                    reflectionColor = traceRay(reflectionRay, new_depth, triangles, materials, numTriangles, light, prev_color);
                    
                    // Zastosowanie współczynnika odbicia (Ks)
                    Color specularColor = materials[mat_inx].getSpectularColor();
                    reflectionColor = reflectionColor.multColor(specularColor);
                }
                return ambientColor.add(diffusColor).add(emitColor).add(reflectionColor);
            }
            break;
        }
    }
    return Color(0.0, 0.0, 0.0);
}