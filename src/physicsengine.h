#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H
#include "entity.h"
#include <vector>
#include <algorithm>
class Entity;
struct collisionBoxValue{
    Entity* entity;
    float Value;
    bool isStart;

};

class PhysicsEngine
{

public:
    PhysicsEngine();
    void collectCollisionValuesFromRoot(Entity* root);
    void collectCollisionValue(Entity *e,std::vector<float> collisionValues);
    void resolveCollisionsFromRoot(Entity* root);
    void printCollisionValues();
    void clearCollisionValues();
    std::vector<std::vector<int>> colideCheck();

private:
    void sortCollisionValues();
    void recursiveCollect(Entity root,int granularity);
    std::vector<collisionBoxValue> cBVx;
    std::vector<collisionBoxValue> cBVy;
    std::vector<collisionBoxValue> cBVz;

};



#endif // PHYSICSENGINE_H
