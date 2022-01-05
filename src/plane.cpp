#include "plane.h"

Plane::Plane()
{
    this->vertex=std::vector<vec3>();


    this->vertex.push_back(vec3(-1.0,-1.0,0.0));
    this->vertex.push_back(vec3(1.0,-1.0,0.0));
    this->vertex.push_back(vec3(1.0,1.0,0.0));
    this->vertex.push_back(vec3(-1.0,1.0,0.0));



    this->ids={0,1,2,1,2,3};

}
Plane::Plane(float size){
    this->vertex=std::vector<vec3>();


    this->vertex.push_back(vec3(-size,-size,0.0));
    this->vertex.push_back(vec3(size,-size,0.0));
    this->vertex.push_back(vec3(size,size,0.0));
    this->vertex.push_back(vec3(-size,size,0.0));

    this->ids={0,1,2,1,2,3};

}

Plane::Plane(float sizeX,float sizeZ){
    this->vertex=std::vector<vec3>();


    this->vertex.push_back(vec3(-sizeX,0.0,-sizeZ));
    this->vertex.push_back(vec3(sizeX,0.0,-sizeZ));
    this->vertex.push_back(vec3(sizeX,0.0,sizeZ));
    this->vertex.push_back(vec3(-sizeX,0.0,sizeZ));

    ids={0,1,2,1,2,3};

}

std::vector<float> Plane::getAABB(Transformation t){
    std::vector<float> collisionArea = std::vector<float>();
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
   collisionArea.push_back(minX);
   collisionArea.push_back(maxX);
   collisionArea.push_back(minY);
   collisionArea.push_back(maxY);
   collisionArea.push_back(minZ);
   collisionArea.push_back(maxZ);



//Constructing AABB according to the same logic as the cube construction
//   collisionArea.push_back(vec3(minX,minY,minZ));
//   collisionArea.push_back(vec3(minX,maxY,minZ));
//   collisionArea.push_back(vec3(minX,minY,maxZ));
//   collisionArea.push_back(vec3(minX,maxY,maxZ));


//   collisionArea.push_back(vec3(maxX,minY,minZ));
//   collisionArea.push_back(vec3(maxX,maxY,minZ));
//   collisionArea.push_back(vec3(maxX,minY,maxZ));
//   collisionArea.push_back(vec3(maxX,maxY,maxZ));

    return collisionArea;
}

std::vector<float> Plane::getCollisonArea(int granularity,Transformation myEntityTransfo) {
 std::vector<float> collisionArea = std::vector<float>();
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

