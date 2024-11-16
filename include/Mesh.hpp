#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Triangle.hpp"
#include <algorithm>


//===========================Mesh===============================================================//
//klasa korzyta z obiektów Vector3D
//klasa korzysta z struktur Face textureCoord
//klasa parsuje pliki .obj do c++
#pragma once
struct Face
{
    std::vector<int> vertexIndices;
    std::vector<int> texCoordIndices;
    std::vector<int> normalIndices;
    int material_index;
};
struct textureCoord
{
    float u, v;
};
class Mesh
{
    private:
        std::vector<Vector3D> vertices;
        std::vector<Vector3D> normals;
        std::vector<Face> faces;
        std::vector<textureCoord> texCoords;
        std::vector<Material> matirals;
        std::vector<Triangle> triangles;
    private:
        bool loadFileOBJ(const std::string& filePath); //metoda parsująca plik
        bool loadFileMTL(const std::string& filePath); //parsowanie mtl
        void faceToTriangle(const Face& face); // zapianie face w trójkącikach
    public:
        Mesh();
        bool loadFiles(const std::string& filePathMTL, const std::string& filePathOBJ);//zbiorcze parsowanie
        bool mollerTrumbore(const Ray ray, Vector3D v0, Vector3D v1, Vector3D v2);

};