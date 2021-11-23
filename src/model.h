#ifndef MODEL_H
#define MODEL_H
#include "vec.h"
#include <vector>
#include <iostream>
class Transformation;


#include "transformation.h"


class Model
{
public:
    Model();
    Model(std::vector<vec3> vert, std::vector<unsigned int> indices);

    std::vector<vec3> render(Transformation transfo);

//    std::vector<vec3> getVertices();
//    void setVertices(std::vector<vec3> newVertices);

//    std::vector<unsigned int> getIds();
//    void setIds(std::vector<unsigned int> newIds);

//private:
    std::vector<vec3> vertex;
    std::vector<unsigned int> ids;

};

#endif // MODEL_H
