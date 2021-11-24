#include "cube.h"

Cube::Cube()
{
    this->vertex=std::vector<vec3>();


    this->vertex.push_back(vec3(-1.0,-1.0,-1.0));
    this->vertex.push_back(vec3(-1.0,1.0,-1.0));
    this->vertex.push_back(vec3(-1.0,-1.0,1.0));
    this->vertex.push_back(vec3(-1.0,1.0,1.0));

    this->vertex.push_back(vec3(1.0,-1.0,-1.0));
    this->vertex.push_back(vec3(1.0,1.0,-1.0));
    this->vertex.push_back(vec3(1.0,-1.0,1.0));
    this->vertex.push_back(vec3(1.0,1.0,1.0));

    this->ids={0,1,2,1,2,3,
         1,7,5,3,7,1,
         5,6,4,7,6,5,
         6,0,2,0,6,4,
         2,6,7,2,7,3,
         0,1,5,0,5,4};

}

Cube::Cube(float size){
    vertex=std::vector<vec3>();


    vertex.push_back(vec3(-size,-size,-size));
    vertex.push_back(vec3(-size,size,-size));
    vertex.push_back(vec3(-size,-size,size));
    vertex.push_back(vec3(-size,size,size));

    vertex.push_back(vec3(size,-size,-size));
    vertex.push_back(vec3(size,size,-size));
    vertex.push_back(vec3(size,-size,size));
    vertex.push_back(vec3(size,size,size));

    ids={0,1,2,1,2,3,
         1,7,5,3,7,1,
         5,6,4,7,6,5,
         6,0,2,0,6,4,
         2,6,7,2,7,3,
         0,1,5,0,5,4};
}

std::vector<vec3> Cube::getCollisonArea(int granularity) {

}
