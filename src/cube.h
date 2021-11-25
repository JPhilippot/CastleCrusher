#ifndef CUBE_H
#define CUBE_H
#include "model.h"

class Cube : public Model
{
public:
    Cube();
    Cube(float size);
    std::vector<vec3> getCollisonArea(int granularity,Transformation myEntityTransfo) override;
private:
   std::vector<vec3> getAABB(Transformation t);
};

#endif // CUBE_H
