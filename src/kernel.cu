#include "../include/kernel.h"

/*__device__ float randomFloat(curandState* state) {
    return curand_uniform(state);
};

__global__ void renderKernel(Color* d_image, int width, int height, int samples, Triangle* d_triangles, int numTriangles, Material* d_materials, Light light, Camera camera) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < width && y < height) {

        int pixelIdx = y * width + x; // indeks pixela
        
        // Inicjalizacja stanu generatora CURAND
        curandState state;
        curand_init(1234, pixelIdx, 0, &state);

        Ray ray = camera.getRay(x, y);  // Generowanie promienia dla danego piksela
        float u = (x + randomFloat(&state)) / width;
        float v = (y + randomFloat(&state)) / height;

        // Śledzenie promienia
        Color color = TraceRay::traceRay(ray, 10, d_triangles, d_materials, numTriangles, light);

        // Zapis koloru do obrazu
        d_image[pixelIdx] = color;
    }
}*/
__device__ float randomFloat(curandState* state) {
    return curand_uniform(state); // Losowa liczba zmiennoprzecinkowa [0, 1)
}

__global__ void renderKernel(Color* d_image, int width, int height, int samples, Triangle* d_triangles, int numTriangles, Material* d_materials, Light light, Camera camera) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < width && y < height) {
        int pixelIdx = y * width + x; // Indeks piksela

        // Inicjalizacja stanu generatora CURAND
        curandState state;
        curand_init(1234, pixelIdx, 0, &state);

        // Zmienna do sumowania kolorów
        Color accumulatedColor(0.0f, 0.0f, 0.0f);

        // Supersampling: wykonywanie wielu próbek na piksel
        for (int s = 0; s < samples; ++s) {
            float u = (x + randomFloat(&state)) / width;
            float v = (y + randomFloat(&state)) / height;

            Ray ray = camera.getRay(u, v); // Generowanie promienia dla losowego punktu w obrębie piksela

            // Śledzenie promienia
            Color color = TraceRay::traceRay(ray, 3, d_triangles, d_materials, numTriangles, light, Color(0.0, 0.0, 0.0));

            // Dodanie koloru do sumy
            accumulatedColor = accumulatedColor.add(color);
        }

        // Uśrednianie kolorów z próbek
        accumulatedColor = accumulatedColor.mult(1.0f / samples);

        // Zapis koloru do obrazu
        d_image[pixelIdx] = accumulatedColor;
    }
}
