#include <iostream>
#include "../include/Mesh.hpp"

int main()
{
    Vector3D wek(3.0,34.2,7.1);
    Vector3D wek2(4.0,34.2,44.2);
    Ray ray(wek,wek2);
    Mesh obj;
    obj.loadFiles("/home/tobiasz/pathtracerGUI2024/data/Earth2K.mtl", "/home/tobiasz/pathtracerGUI2024/data/Earth2K.obj");
    return 0;
}