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

std::vector<vec3> Cube::getAABB(Transformation t){
    std::vector<vec3> collisionArea = std::vector<vec3>();
    std::vector<vec3> transformedVertices= std::vector<vec3>();
    float maxX = -999999.9f, maxY= -999999.9f, maxZ = -999999.9f;
    float minX = 999999.9f, minY= 999999.9f, minZ = 999999.9f;
   for(size_t i = 0; i<this->vertex.size(); i++){
      vec3 temp = t.apply(vertex.at(i));
        transformedVertices.push_back(temp);
        maxX= (maxX<temp.x? temp.x:maxX);
        maxY= (maxY<temp.y? temp.y:maxY);
        maxZ= (maxZ<temp.z? temp.z:maxZ);

        minX= (minX>temp.x? temp.x:minX);
        minY= (minY>temp.y? temp.y:minY);
        minZ= (minZ>temp.z? temp.z:minZ);
    }

//Constructing AABB according to the same logic as the cube construction
   collisionArea.push_back(vec3(minX,minY,minZ));
   collisionArea.push_back(vec3(minX,maxY,minZ));
   collisionArea.push_back(vec3(minX,minY,maxZ));
   collisionArea.push_back(vec3(minX,maxY,maxZ));


   collisionArea.push_back(vec3(maxX,minY,minZ));
   collisionArea.push_back(vec3(maxX,maxY,minZ));
   collisionArea.push_back(vec3(maxX,minY,maxZ));
   collisionArea.push_back(vec3(maxX,maxY,maxZ));

    return collisionArea;
}
std::vector<vec3> Cube::getCollisonArea(int granularity,Transformation myEntityTransfo) {
 std::vector<vec3> collisionArea = std::vector<vec3>();
    switch (granularity){
    case 0 :
        collisionArea = getAABB(myEntityTransfo);
        break;
    default:
        std::cout<<"Invalid collision area granularity \n";
        break;
    }
    return collisionArea;
}

