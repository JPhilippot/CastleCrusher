#ifndef CUBE_H
#define CUBE_H
#include "model.h"

class Cube : public Model
{
public:
    shape myShape = CUBE;
    Cube();

    Cube(float size);
    std::vector<float> getCollisonArea(int granularity,Transformation myEntityTransfo) override;
    //Interval getInterval(Transformation t, vec3 axis);
private:
   std::vector<float> getAABB(Transformation t);
};

#endif // CUBE_H
