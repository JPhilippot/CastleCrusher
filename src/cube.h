#ifndef CUBE_H
#define CUBE_H
#include "model.h"

class Cube : public Model
{
public:
    Cube();
    Cube(std::vector<vec3> vert, std::vector<unsigned int> indices);
    Cube(float size);
};

#endif // CUBE_H
