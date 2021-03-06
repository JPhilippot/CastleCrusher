#ifndef OBJECT_H
#define OBJECT_H

#include "vec.h"
#include "mat.h"
#include <vector>
#include <iostream>

class Transformation;


#include "transformation.h"


//using namespace std;



class Object
{
public:

    enum Shape{
        CUBE,
        PLANE,
        SPHERE
    };

    std::vector<vec3> vertex;
    Shape shape;
    std::vector<unsigned int> ids;
    Object(std::vector<vec3> vert, std::vector<unsigned int> indices);
    Object();

    Object(Shape myShape, float size);
    std::vector<vec3> render(Transformation transfo);
};

#endif // OBJECT_H
