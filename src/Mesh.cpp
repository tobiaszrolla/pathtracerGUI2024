#include "../include/Mesh.hpp"
#include <cmath>
#include <vector>


Mesh::Mesh()
{};

bool Mesh::loadFileOBJ(const std::string& filePath) {
    // Otwieranie pliku
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open a file");
        return false;
    }

    std::string line;
    int materialIndex = -1; // Indeks materiału, domyślnie -1
    std::string currentObject; // Nazwa bieżącego obiektu

    // Wczytanie danych obiektu
    while (std::getline(file, line)) {
        std::istringstream streamLine(line);
        std::string type;
        streamLine >> type;

        if (type == "o") { // Nowy obiekt
            streamLine >> currentObject;
        }
        else if (type == "v") { // Współrzędne wierzchołków
            float x, y, z;
            streamLine >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        }
        else if (type == "vn") { // Współrzędne wektorów normalnych
            float nx, ny, nz;
            streamLine >> nx >> ny >> nz;
            normals.emplace_back(nx, ny, nz);
        }
        else if (type == "vt") { // Współrzędne tekstur
            textureCoord texCoord;
            streamLine >> texCoord.u >> texCoord.v;
            tex_coords.push_back(texCoord);
        }
        else if (type == "usemtl") { // Użycie nowego materiału
            materialIndex++;
        }
        else if (type == "f") { // Twarze obiektów
            Face face;
            std::string faceData;

            while (streamLine >> faceData) {
                std::replace(faceData.begin(), faceData.end(), '/', ' ');
                std::istringstream faceStream(faceData);

                int vertexIndex = 0, texCoordIndex = 0, normalIndex = 0;
                faceStream >> vertexIndex >> texCoordIndex >> normalIndex;

                face.vertexIndices.push_back(vertexIndex - 1);
                face.texCoordIndices.push_back(texCoordIndex - 1);
                face.normalIndices.push_back(normalIndex - 1);
            }

            face.material_index = materialIndex;
            faces.push_back(face);
        }
    }
    return true;
}

bool Mesh::loadFileMTL(const std::string& filePath){
    //otwieranie pliku
    std::ifstream  file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open a file");
        return false;//to nie jest potrzebne ale zostawie żeby kompilator nie płakał
    }

    std::string line;
    Material currentMaterial;
    std::string materialName;

    while (std::getline(file, line)) {
            
            //string stream
            std::istringstream iss(line);
            std::string type;
            iss >> type;

        if(type == "newmtl")  // nowy materiał
        {
            iss >> materialName;
        }
        else if(type == "Ka")  // ambient kolor
        {
            float R, G, B;
            iss >> R >> G >> B;
            currentMaterial.ambient_color = Color(R,G,B);
        }
        else if(type == "Kd")  //dyffuse color rozproszone 
        {
            float R, G, B;
            iss >> R >> G >> B;
            currentMaterial.difus_color = Color(R,G,B);
        }
        else if(type == "Ks")  //secul color kolor odbicia
        {
            float R, G, B;
            iss >> R >> G >> B;
            currentMaterial.secul_color = Color(R,G,B);
        }
        else if(type == "Ke")  //emit color kolor świecenia
        {
            float R, G, B;
            iss >> R >> G >> B;
            currentMaterial.emit_color = Color(R,G,B);
        }
        else if(type == "Ns")  //współczynnik odbicia
        {
            float shines;
            iss >> shines;
            currentMaterial.shines = shines;
        }
        else if(type == "Ni") //współczynnik załamania po przejściu przez obiekt
        {
            float refraction;
            iss >> refraction;
            currentMaterial.refraction = refraction;
        }
        else if(type == "d") //przezroczystość
        {
            iss >> currentMaterial.transp;
        }
        else if(type == "Tr") //równierz przezroczystość
        {
            float trans;
            iss >> trans;
            currentMaterial.transp = 1.0f - trans;
        }
        else if(type == "illum")  //model oświetlenia jak materiał reaguje
        {
            int ilum;
            iss >> ilum;
            currentMaterial.lightModel = ilum;
            matirals.push_back(currentMaterial);
            currentMaterial = Material();
        }
    }
    return true;
};
void Mesh::faceToTriangle(const Face& face){
    // Podziel czworokąt na dwa trójkąty
    if (face.vertexIndices.size() == 4)
    {
        // Trójkąt 1: wierzchołki 0, 1, 2
        Triangle triangle1(
            vertices[face.vertexIndices[0]],  // Wierzchołek 0
            vertices[face.vertexIndices[1]],  // Wierzchołek 1
            vertices[face.vertexIndices[2]],  // Wierzchołek 2
            face.material_index
        );

        triangles.push_back(triangle1);

        // Trójkąt 2: wierzchołki 0, 2, 3
        Triangle triangle2(
            vertices[face.vertexIndices[0]],  // Wierzchołek 0
            vertices[face.vertexIndices[2]],  // Wierzchołek 2
            vertices[face.vertexIndices[3]],  // Wierzchołek 3
            face.material_index
        );
        triangles.push_back(triangle2);
    }
    //Trójkąt wszystko super
    else if (face.vertexIndices.size() == 3)
    {
        Triangle triangle(
            vertices[face.vertexIndices[0]],  // Wierzchołek 0
            vertices[face.vertexIndices[1]],  // Wierzchołek 1
            vertices[face.vertexIndices[2]],  // Wierzchołek 2
            face.material_index
        );
        triangles.push_back(triangle);
    }
};
bool Mesh::loadFiles(const std::string& filePathMTL, const std::string& filePathOBJ){
    bool ret = false;
    ret = loadFileMTL(filePathMTL); //ładowanie .mtl materiały
    ret = loadFileOBJ(filePathOBJ); //ładowanie .obj wierzchołki

    //przepisanie faces na trójkąty
    for(auto& face : faces)
    {
        faceToTriangle(face);
    }
    return ret;
};

std::vector<Material> Mesh::getMaterials() const {
    return matirals;
};

std::vector<Triangle> Mesh::getTriangles() const {
    return triangles;
}

Vector3D Mesh::maxPositions() const {
    float max_x = 0.0, max_y = 0.0, max_z = 0.0;
    for(Vector3D vertex : vertices)
    {
        if(vertex.getX()>max_x)
        {
            max_x = vertex.getX();
        }
        if(vertex.getY()>max_y)
        {
            max_y = vertex.getY();
        }
        if(vertex.getZ()>max_z)
        {
            max_z = vertex.getZ();
        }
    }
    return Vector3D(max_x,max_y,max_z);
};

Vector3D Mesh::center() const {
    //średnia wszystkich położeń
    float y_es = 0, z_es = 0, x_es = 0;
    for(Vector3D vertex: vertices)
    {
        x_es += vertex.getX();
        y_es += vertex.getY();
        z_es += vertex.getZ();
    }
    return Vector3D(x_es/vertices.size(), y_es/vertices.size(), z_es/vertices.size());
};

    