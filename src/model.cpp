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

//std::vector<vec3> Model::getVertices(){
//    return *vertex;
//}
//void Model::setVertices(std::vector<vec3> newVertices){
//    this->vertex
//}

//std::vector<unsigned int> Model::getIds(){

//}
//void Model::setIds(std::vector<unsigned int> newIds){

//}
