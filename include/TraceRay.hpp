#include "Light.hpp"

class TraceRay
{
    public:
        __device__ static Color traceRay(Ray& ray, 
                                int depth, 
                                Triangle* triangles, 
                                Material* materials, 
                                int numTriangles, 
                                Light light,
                                Color prev_color);
    private:
        __device__ static bool isInShadow(Vector3D point, Vector3D& lightDir, Triangle* triangles, int numTriangles);
        
};