#ifndef COLLIDER_H
#define COLLIDER_H
#include <iostream>
#include "entity.h"
#include "model.h"
#include "transformation.h"



class Collider
{
public:
    Collider();
    Collider(Entity* enityToBind, bool binded = true);
    bool collidesWith(Entity otherEntity);

    bool isBinded();
private:
    bool bind;
    Entity* bindedEntity;


};

#endif // COLLIDER_H
