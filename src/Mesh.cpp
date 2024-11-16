#include "../include/Mesh.hpp"
#include <cmath>


Mesh::Mesh(){};
bool Mesh::loadFileOBJ(const std::string& filePath)
{
    std::ifstream  file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open a file");
        return false;//to nie jest potrzebne ale zostawie żeby kompilator nie płakał
    }
    std::string line;
    int materialIndex = -1; //ustawiam na -1 bo pierw jest informacja o materiale a potem faces
    while (std::getline(file, line)) 
    {
        std::istringstream streamLine(line);
        std::string type;
        streamLine >> type;
        if(type == "v")
        {
            float x,y,z;
            streamLine >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        }
        else if(type == "vn")
        {
            float nx,ny,nz;
            streamLine >> nx >> ny >> nz;
            vertices.emplace_back(nx, ny, nz);
        }
        else if(type == "vt")
        {
            textureCoord texCoord;
            streamLine >> texCoord.u >> texCoord.v;
            texCoords.push_back(texCoord);
        }
        else if(type == "usemtl")
        {
            materialIndex++;
        }
        else if(type == "f") //Face format f num/num/num trzeba się pozbyć replacem
        {
            Face face;
            std::string FaceData;
            while(streamLine >> FaceData)
            {
                std::replace(FaceData.begin(), FaceData.end(), '/', ' ');
                std::istringstream FaceStream(FaceData);
                int vertexIndex = 0, texCoordIndex = 0, normalIndex = 0;
                FaceStream >> vertexIndex >> texCoordIndex >> normalIndex;

                face.vertexIndices.push_back(vertexIndex - 1);
                face.texCoordIndices.push_back(texCoordIndex - 1);
                face.normalIndices.push_back(normalIndex - 1);
                face.material_index = materialIndex;
            }
            faces.push_back(face);
        }
    }
    return true; 
};

bool Mesh::loadFileMTL(const std::string& filePath)
{
    std::ifstream  file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open a file");
        return false;//to nie jest potrzebne ale zostawie żeby kompilator nie płakał
    }

    std::string line;
    Material currentMaterial;
    std::string materialName;

    while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string type;
            iss >> type;
        if(type == "newmtl")
        {
            iss >> materialName;
        }
        else if(type == "Ka")
        {
            float R, G, B;
            iss >> R >> G >> B;
            currentMaterial.ambientColor = Vector3D(R,G,B);
        }
        else if(type == "Kd")
        {
            float R, G, B;
            iss >> R >> G >> B;
            currentMaterial.difusColor = Vector3D(R,G,B);
        }
        else if(type == "Ks")
        {
            float R, G, B;
            iss >> R >> G >> B;
            currentMaterial.seculColor = Vector3D(R,G,B);
        }
        else if(type == "Ke")
        {
            float R, G, B;
            iss >> R >> G >> B;
            currentMaterial.emitColor = Vector3D(R,G,B);
        }
        else if(type == "Ns")
        {
            float shines;
            iss >> shines;
            currentMaterial.shines = shines;
        }
        else if(type == "Ni")
        {
            float refraction;
            iss >> refraction;
            currentMaterial.refraction = refraction;
        }
        else if(type == "d") 
        {
            iss >> currentMaterial.transp;
        }
        else if(type == "Tr") 
        {
            float trans;
            iss >> trans;
            currentMaterial.transp = 1.0f - trans;
        }
        else if(type == "illum")
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
void Mesh::faceToTriangle(const Face& face)
{
    if (face.vertexIndices.size() == 4)
    {
        // Podziel czworokąt na dwa trójkąty
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
    else if (face.vertexIndices.size() == 3)
    {
        // Jeśli face to trójkąt, po prostu dodaj go do listy trójkątów
        Triangle triangle(
            vertices[face.vertexIndices[0]],  // Wierzchołek 0
            vertices[face.vertexIndices[1]],  // Wierzchołek 1
            vertices[face.vertexIndices[2]],  // Wierzchołek 2
            face.material_index
        );
        triangles.push_back(triangle);
    }
};
bool Mesh::loadFiles(const std::string& filePathMTL, const std::string& filePathOBJ)
{
    bool ret = false;
    ret = loadFileMTL(filePathMTL);
    ret = loadFileOBJ(filePathOBJ);
    for(auto& face : faces)
    {
        faceToTriangle(face);
    }
    return ret;
};


    