#include "model.h"

Model::Model(){
}
std::vector<vec3> Model::render(Transformation transfo){
    std::vector<vec3> res;
    for (int i=0;i<this->vertex.size();i++){
        res.push_back(vec3(transfo.apply(vertex[i])));
    }
    return res;
}
std::vector<float> Model::getCollisonArea(int granularity, Transformation myEntityTransfo){
    //please specify this function in child
}
