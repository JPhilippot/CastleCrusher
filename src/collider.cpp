#include "collider.h"

Collider::Collider() : bind(false), bindedEntity(nullptr)
{
}

Collider::Collider(Entity* entityToBind, bool isBinded): bind(isBinded), bindedEntity(entityToBind) {

}
bool Collider::collidesWith(Entity otherEntity){
    if(!otherEntity.hasCollider()){
        std::cout<<otherEntity.print() <<"has no collider !"<<std::endl;
        return false;
    }
    if(this->bindedEntity == nullptr){
        std::cout<<"ERROR :No entity binded to this collider ! \n";
        return false;
    }
//    std::vector<vec3> AABB1 = this->bindedEntity->getModel().getCollisonArea(0,this->bindedEntity->getTransfo());
//    std::vector<vec3> AABB2 = otherEntity.getModel().getCollisonArea(0,otherEntity.getTransfo());

//    //Inspired from theBennyBox

//    vec3 dMin1Max2 = AABB1.at(0) - AABB2.at(AABB2.size()-1);
//    vec3 dMin2Max1 = AABB2.at(0) - AABB1.at(AABB1.size()-1);
//    vec3 distanceMax = vec3((dMin1Max2.x > dMin2Max1.x? dMin1Max2.x: dMin2Max1.x),(dMin1Max2.y > dMin2Max1.y? dMin1Max2.y: dMin2Max1.y),(dMin1Max2.z > dMin2Max1.z? dMin1Max2.z: dMin2Max1.z));
//    float maxAxisDistance = (distanceMax.x > distanceMax.y ? (distanceMax.x >distanceMax.z ? distanceMax.x : distanceMax.z): (distanceMax.y > distanceMax. z ? distanceMax.y : distanceMax.z));

//    std::cout<<"Distance between "<< this->bindedEntity->getEntityName().toStdString()<< " and " << otherEntity.getEntityName().toStdString()<< "is " << maxAxisDistance<<std::endl;
//    return maxAxisDistance <= 0;
    return false;
}
