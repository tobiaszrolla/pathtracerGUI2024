#include "../include/PathTracer.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

float PathTracer::randomFloat() const
{
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator;
    return distribution(generator);
}

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
PathTracer::PathTracer(): width(1920), height(1080), samples(10){};

PathTracer::PathTracer(int x, int y, int samp): width(x), height(y), samples(samp){}

void PathTracer::generateImage(Mesh mesh)
{
    std::vector<Triangle> triangles = mesh.getTriangles();
    std::vector<Material> materiales = mesh.getMaterials();

    std::vector<Color> image(height*width);//wektor obrazu spłaszczony!
    
    float aspect_ratio = width / height;
    Vector3D center = mesh.center();
     Camera camera(120,aspect_ratio,center,-center.getX(),-center.getY(),-center.getZ());
     Vector3D lightPosition = Vector3D(0,0,0);
     //ightPosition.add(center);
     Light light = Light(lightPosition,Color(0.5, 0.5, 0.5),1);

    for (int j = 0; j < height; ++j) 
    {
        for (int k = 0; k < width; ++k)
        {
            Color pixelColor(0.7,0.0,0.0);//pixel start na czarno

            //MonteCarlo
            for (int i = 0; i < samples; i++)
            {
                float u = (float(k) + randomFloat()) / (width); // Drobna losowość dla antyaliasingu
                float v = (float(j) + randomFloat()) / (height);

                Ray ray = camera.getRay(u, v);
                pixelColor = pixelColor.add(traceRay(ray, max_depth, triangles, materiales,light));
            }
            // Uśrednianie kolorów po próbkach
            pixelColor = pixelColor.mult(1.0f / float(samples));

            // Normalizacja kolorów (trzymanie wartości w zakresie [0, 1])
            pixelColor.clamp();

            // Zapisz kolor piksela do obrazu
            image[j * width + k] = pixelColor;
        }
    }
    saveImage(image, width, height, "/home/tobiasz/pathtracerGUI2024/image.ppm");
};