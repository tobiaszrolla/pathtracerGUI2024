#include <iostream>
#include "../include/PathTracer.hpp"

int main()
{
    Mesh obj;
    obj.loadFiles("/home/tobi/pathtracerGUI2024/data/peng4.mtl", "/home/tobi/pathtracerGUI2024/data/peng4.obj");
    PathTracer path_tracer;
    path_tracer.generateImage(obj);

    return 0;
}