#ifndef FORCES_H
#define FORCES_H
#include "vec.h"
#include <vector>

class Forces
{
public:
    vec3 F;
    vec3 oldVelocity;   // ?
    vec3 oldPos;        // ?

    Forces();
    Forces(vec3 f);
    Forces (float x, float y, float z);
    //Forces(Forces& cop);

    void addForces(std::vector<Forces> forces);

};

#endif // FORCES_H
