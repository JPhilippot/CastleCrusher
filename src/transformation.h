#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "vec3.h"
//#include "object.h"
//#include "entity.h"


class Transformation
{
public:

    vec3 translation;
    mat3 rotation;
    vec3 scale;

    Transformation();
    Transformation(vec3 trans, mat3 rot, vec3 sc);//
    Transformation(vec3 trans, vec3 rot, vec3 sc);
    Transformation compose(Transformation t);

    Transformation invert();


    vec3 apply(vec3 point);

};

#endif // TRANSFORMATION_H
