#ifndef PLANE_H
#define PLANE_H

#include "model.h"

class Plane: public Model
{
public:
    Plane();
    Plane(float size);
    Plane(float sizeX,float sizeZ); // horizontal plane
    std::vector<float> getCollisonArea(int granularity,Transformation myEntityTransfo) override;
private:
   std::vector<float> getAABB(Transformation t);

};


#endif // PLANE_H
