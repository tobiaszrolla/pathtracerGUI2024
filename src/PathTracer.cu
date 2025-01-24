#include "../include/PathTracer.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cuda_runtime.h> // Dodatkowy include dla cudaDeviceSetLimit
/*
void PathTracer::saveImage(const std::vector<Color>& image, int width, int height, const std::string& filename) const
{
    std::ofstream file(filename, std::ios::trunc);  // Otwórz plik w trybie nadpisywania
    if (!file) {
        std::cerr << "Nie udało się otworzyć pliku do zapisu!" << std::endl;
        return;
    }

    // Nagłówek PPM (P3 dla formatu tekstowego)
    file << "P3\n";
    file << width << " " << height << "\n";
    file << "255\n";  // Maksymalna wartość koloru

    // Zapisujemy każdy piksel obrazu
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Color color = image[i * width + j];  // Pobierz odpowiedni kolor
            int r, g, b;
            color.toPPM(r, g, b);
            file << r << " " << g << " " << b << "\n";
        }
    }
    file.close();
};
PathTracer::PathTracer(): width(960), height(540), samples(10), d_image(nullptr), d_triangles(nullptr), d_materials(nullptr){};

PathTracer::PathTracer(int x, int y, int samp): width(x), height(y), samples(samp){}

PathTracer::~PathTracer()
{
    freeGPUMemory();
}

void PathTracer::generateImage(Mesh mesh)
{
    //Pobierz dane z mesh
    std::vector<Triangle> triangles = mesh.getTriangles();
    std::vector<Material> materiales = mesh.getMaterials();

    //ustawienie kamery światła
    float aspect_ratio = width / height;  //aspect ratio potrzebne do kąta kamey
    Vector3D center = mesh.center();
    Camera camera(120,aspect_ratio,center,-center.getX(),-center.getY(),-center.getZ());
    Vector3D cam_orgin = camera.getOrigin();
    Vector3D lightPosition = Vector3D(0,-5,0);
    Light light = Light(lightPosition,Color(0.5, 0.5, 0.5),1);


    std::sort(triangles.begin(), triangles.end(), [cam_orgin](const Triangle& a, const Triangle& b) {
        return a.center().distanceTo(cam_orgin) < b.center().distanceTo(cam_orgin);
    });
    for(int i = 0; i<triangles.size(); i++)
    {
        std::cout<<triangles[i].center().distanceTo(cam_orgin)<<std::endl;
    }

    //alokowanie pamięci GPU
    allocateGPUMemory(triangles,materiales);
    // Kopiowanie danych do GPU
    copyDataToGPU(triangles, materiales);

    // Konfiguracja GPU
    dim3 blockSize(16, 16); //blok wątków GPU współdzielą zasoby
    dim3 gridSize((width + blockSize.x - 1) / blockSize.x, (height + blockSize.y - 1) / blockSize.y); //siatak składająca się z bloków

    std::vector<Color> image(height*width);//wektor obrazu spłaszczony!
    
    // Wywołanie kernela CUDA
    renderKernel<<<gridSize, blockSize>>>(d_image, width, height, samples, d_triangles, triangles.size(), d_materials, light, camera);

    // Synchronizacja GPU
    cudaDeviceSynchronize();

    // Pobranie wynikowego obrazu z GPU
    std::vector<Color> h_image(width * height);
    cudaMemcpy(h_image.data(), d_image, width * height * sizeof(Color), cudaMemcpyDeviceToHost);

    // Zapis obrazu na dysk
    saveImage(h_image, width, height, "/home/tobi/pathtracerGUI2024/image.ppm");

    // Zwolnienie pamięci GPU
    freeGPUMemory();
};

//CUDA ALOCATE/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Alokacja pamięci na GPU
void PathTracer::allocateGPUMemory(const std::vector<Triangle>& triangles, const std::vector<Material>& materials) {
    cudaMalloc(&d_image, width * height * sizeof(Color));  
    cudaMalloc(&d_triangles, triangles.size() * sizeof(Triangle));  
    cudaMalloc(&d_materials, materials.size() * sizeof(Material));  
}

// Kopiowanie danych do GPU
void PathTracer::copyDataToGPU(const std::vector<Triangle>& triangles, const std::vector<Material>& materials) {
    cudaMemcpy(d_triangles, triangles.data(), triangles.size() * sizeof(Triangle), cudaMemcpyHostToDevice);
    cudaMemcpy(d_materials, materials.data(), materials.size() * sizeof(Material), cudaMemcpyHostToDevice);
}


// Zwolnienie pamięci z GPU
void PathTracer::freeGPUMemory() {
    cudaFree(d_image);
    cudaFree(d_triangles);
    cudaFree(d_materials);
}
*/

void PathTracer::saveImage(const std::vector<Color>& image, int width, int height, const std::string& filename) const
{
    std::ofstream file(filename, std::ios::trunc);  // Otwórz plik w trybie nadpisywania
    if (!file) {
        std::cerr << "Nie udało się otworzyć pliku do zapisu!" << std::endl;
        return;
    }

    // Nagłówek PPM (P3 dla formatu tekstowego)
    file << "P3\n";
    file << width << " " << height << "\n";
    file << "255\n";  // Maksymalna wartość koloru

    // Zapisujemy każdy piksel obrazu
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Color color = image[i * width + j];  // Pobierz odpowiedni kolor
            int r, g, b;
            color.toPPM(r, g, b);
            file << r << " " << g << " " << b << "\n";
        }
    }
    file.close();
};

PathTracer::PathTracer(): width(960), height(540), samples(10), d_image(nullptr), d_triangles(nullptr), d_materials(nullptr){};

PathTracer::PathTracer(int x, int y, int samp): width(x), height(y), samples(samp){}

PathTracer::~PathTracer()
{
    freeGPUMemory();
}

void PathTracer::generateImage(Mesh mesh)
{
    // Zwiększanie limitu stosu CUDA dla głębokiej rekurencji
    size_t stackSize = 16384; // 16 KB na wątek (możesz zwiększyć w razie potrzeby)
    cudaDeviceSetLimit(cudaLimitStackSize, stackSize);

    // Sprawdzenie, czy limit stosu został ustawiony poprawnie
    size_t currentStackSize;
    cudaDeviceGetLimit(&currentStackSize, cudaLimitStackSize);
    std::cout << "Limit stosu ustawiony na: " << currentStackSize << " bajtów" << std::endl;

    // Opcjonalne zwiększenie sterty dla dynamicznej alokacji pamięci na urządzeniu
    size_t heapSize = 128 * 1024 * 1024; // 128 MB
    cudaDeviceSetLimit(cudaLimitMallocHeapSize, heapSize);

    // Pobranie danych z mesh
    std::vector<Triangle> triangles = mesh.getTriangles();
    std::vector<Material> materiales = mesh.getMaterials();

    // Ustawienie kamery i światła
    float aspect_ratio = width / height;  // aspect ratio potrzebne do kąta kamery
    Vector3D center = mesh.center();
    Camera camera(120, aspect_ratio, center, -center.getX(), -center.getY(), -center.getZ());
    Vector3D cam_origin = camera.getOrigin();
    Vector3D lightPosition = Vector3D(-1, -3, 1.5);
    Light light = Light(lightPosition, Color(0.5, 0.5, 0.5), 1);

    std::sort(triangles.begin(), triangles.end(), [cam_origin](const Triangle& a, const Triangle& b) {
        return a.center().distanceTo(cam_origin) < b.center().distanceTo(cam_origin);
    });

    // Alokowanie pamięci GPU
    allocateGPUMemory(triangles, materiales);

    // Kopiowanie danych do GPU
    copyDataToGPU(triangles, materiales);

    // Konfiguracja GPU
    dim3 blockSize(16, 16); // blok wątków GPU współdzielą zasoby
    dim3 gridSize((width + blockSize.x - 1) / blockSize.x, (height + blockSize.y - 1) / blockSize.y); // siatka składająca się z bloków

    std::vector<Color> image(height * width); // Wektor obrazu spłaszczony

    // Wywołanie kernela CUDA
    renderKernel<<<gridSize, blockSize>>>(d_image, width, height, samples, d_triangles, triangles.size(), d_materials, light, camera);

    // Synchronizacja GPU
    cudaDeviceSynchronize();

    // Pobranie wynikowego obrazu z GPU
    std::vector<Color> h_image(width * height);
    cudaMemcpy(h_image.data(), d_image, width * height * sizeof(Color), cudaMemcpyDeviceToHost);

    // Zapis obrazu na dysk
    saveImage(h_image, width, height, "/home/tobi/pathtracerGUI2024/image.ppm");

    // Zwolnienie pamięci GPU
    freeGPUMemory();
}

// CUDA ALOCATE /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PathTracer::allocateGPUMemory(const std::vector<Triangle>& triangles, const std::vector<Material>& materials) {
    cudaMalloc(&d_image, width * height * sizeof(Color));  
    cudaMalloc(&d_triangles, triangles.size() * sizeof(Triangle));  
    cudaMalloc(&d_materials, materials.size() * sizeof(Material));  
}

void PathTracer::copyDataToGPU(const std::vector<Triangle>& triangles, const std::vector<Material>& materials) {
    cudaMemcpy(d_triangles, triangles.data(), triangles.size() * sizeof(Triangle), cudaMemcpyHostToDevice);
    cudaMemcpy(d_materials, materials.data(), materials.size() * sizeof(Material), cudaMemcpyHostToDevice);
}

void PathTracer::freeGPUMemory() {
    cudaFree(d_image);
    cudaFree(d_triangles);
    cudaFree(d_materials);
}
