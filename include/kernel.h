#ifndef KERNEL_H
#define KERNEL_H

#include <curand_kernel.h>
#include "TraceRay.hpp"

__device__ float randomFloat(curandState* state);
__global__ void renderKernel(Color* d_image, int width, int height, int samples, Triangle* d_triangles, int numTriangles, Material* d_materials, Light light, Camera camera);

#endif  // KERNEL_H