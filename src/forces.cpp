#include "forces.h"

Forces::Forces()
{
    F=vec3();
}

Forces::Forces(vec3 f){
    F=vec3(f);
    oldVelocity=vec3(0.0,0.0,0.0);
    oldPos=vec3(0.0,0.0,0.0);
}
Forces::Forces (float x, float y, float z){
    F=vec3(x,y,z);
    oldVelocity=vec3(0.0,0.0,0.0);
    oldPos=vec3(0.0,0.0,0.0);
}

//Forces::Forces(Forces& cop){
//    F=cop.F;
//    oldPos=cop.oldPos;
//    oldVelocity=cop.oldVelocity;
//}

void Forces::addForces(std::vector<Forces> forces){
    for (int i=0; i<forces.size();i++){
        F.x+=forces[i].F.x;
        F.y+=forces[i].F.y;
        F.z+=forces[i].F.z;
    }
}


