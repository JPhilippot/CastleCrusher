#ifndef MODEL_H
#define MODEL_H
#include "vec.h"
#include <vector>
#include <iostream>
class Transformation;


#include "transformation.h"

enum shape{
    CUBE,
    SPHERE,
    PLANE
};

struct Interval{
    float min;
    float max;
};

class Model
{
public:
    shape myShape;
    Model();
    //Model(std::vector<vec3> vert, std::vector<unsigned int> indices);
    Model(float size);
    std::vector<vec3> render(Transformation transfo);

    virtual std::vector<float> getCollisonArea(int granularity, Transformation myEntityTransfo) = 0;// Je décide de calculer la zone de collision directement dans le modèle, en fonction de la granularité désirée. Cette zone va être renvoyée dans un vector lors de son appel, dans Collider::collidesWith(), et c'est dans cette fonction qu'en fonction on va demander une zone de collision plus ou moins fine (granularité : AABB -> PCA -> CH);
    std::vector<vec3> vertex;
    std::vector<unsigned int> ids;

};

#endif // MODEL_H
