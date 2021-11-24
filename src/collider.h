#ifndef COLLIDER_H
#define COLLIDER_H
#include "model.h"

class Collider
{
public:
    Collider();

    bool collidesWith(Model myModel ,Model otherModel);



};

#endif // COLLIDER_H
