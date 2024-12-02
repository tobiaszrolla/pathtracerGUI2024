//dobra PathTracer
#include "TraceRay.hpp"
class PathTracer : public TraceRay
{
    private:
        const int max_depth = 20;
        float height;
        float width;
        int samples;
        std::vector<Triangle> triangles;
        std::vector<Material> materiales;
    private:
        float randomFloat() const;
        //Color traceRay(Ray &ray, int depth, const std::vector<Triangle> &triangles, const std::vector<Material> &materiales, const Light& light) const;
        void saveImage(const std::vector<Color>& image, int width, int height, const std::string& filename) const;
    public:
        PathTracer();
        PathTracer(int x, int y, int samp);
        void generateImage(Mesh mesh);
        
};