//dobra PathTracer
#include "kernel.h"
class PathTracer
{
    private:
        //const int max_depth = 20;
        float height;
        float width;
        int samples;

        // Wskaźniki do pamięci GPU
        Color* d_image;
        Triangle* d_triangles;
        Material* d_materials;
    private:
        //Color traceRay(Ray &ray, int depth, const std::vector<Triangle> &triangles, const std::vector<Material> &materiales, const Light& light) const;
        void saveImage(const std::vector<Color>& image, int width, int height, const std::string& filename) const;
        void allocateGPUMemory(const std::vector<Triangle>& triangles, const std::vector<Material>& materials);
        void copyDataToGPU(const std::vector<Triangle>& triangles, const std::vector<Material>& materials);
        void freeGPUMemory();
    public:
        PathTracer();
        ~PathTracer();
        PathTracer(int x, int y, int samp);
        void generateImage(Mesh mesh);
        
};