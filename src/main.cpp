#include <iostream>
#include "../include/PathTracer.hpp"

int main()
{
    Vector3D wek(3.0,34.2,7.1);
    Vector3D wek2(4.0,34.2,44.2);
    Ray ray(wek,wek2);
    Mesh obj;
    obj.loadFiles("/home/tobiasz/pathtracerGUI2024/pythonAPI/data/penguin.mtl", "/home/tobiasz/pathtracerGUI2024/pythonAPI/data/penguin.obj");
    PathTracer path_tracer;
    path_tracer.generateImage(obj);

    return 0;
}