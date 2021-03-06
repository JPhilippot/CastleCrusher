#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H
#include "entity.h"
#include "forces.h"
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
    std::vector<std::vector<int>> collideCheck();
    std::vector<std::vector<int>> removeDuplicates(std::vector<std::vector<int>> objs);
    std::vector<std::vector<int>> narrowPhase(std::vector<std::vector<Entity*>> collidingEntities);

    void applyForces(Entity *e);

    vec3 gravity = vec3(0.0,-9.1,0.0);

private:
    void sortCollisionValues();
    void recursiveCollect(Entity root,int granularity);
    std::vector<collisionBoxValue> cBVx;
    std::vector<collisionBoxValue> cBVy;
    std::vector<collisionBoxValue> cBVz;

};



#endif // PHYSICSENGINE_H
