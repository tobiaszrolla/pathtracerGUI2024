#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Triangle.hpp"



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
        std::vector<textureCoord> tex_coords;
        std::vector<Material> matirals;
        std::vector<Triangle> triangles;
    private:
        bool loadFileOBJ(const std::string& file_path); //metoda parsująca plik
        bool loadFileMTL(const std::string& file_path); //parsowanie mtl
        void faceToTriangle(const Face& face); // zapianie face w trójkącikach
    public:
        //konstruktor ładowanie pliku zapis
        Mesh();
        bool loadFiles(const std::string& file_path_MTL, const std::string& file_path_OBJ);//zbiorcze parsowanie

        //zwracanie orientacji obiektu
        Vector3D maxPositions() const;
        Vector3D center() const;

        //getery
        std::vector<Material> getMaterials() const;
        std::vector<Triangle> getTriangles() const;

};