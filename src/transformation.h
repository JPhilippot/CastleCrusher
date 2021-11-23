#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "vec.h"
#include "mat.h"
//#include "object.h"
//#include "entity.h"


class Transformation
{
public:

//    mat4 translation;
//    mat4 rotation;
//    mat4 scale;
    mat4 transfo;
    //vec3 rpf=vec3(0.0,0.0,0.0);

    Transformation();
    Transformation(vec3 trans, mat4 rot, vec3 sc);//
    //Transformation(vec3 trans, mat4 rot, vec3 sc, vec3 rpf);
    Transformation(mat4 mat);
    Transformation(mat4 mat, vec3 myrpf);
    Transformation(vec3 trans, vec3 rot, vec3 sc);
    //Transformation(vec3 trans, vec3 rot, vec3 sc, vec3 rpf);
    Transformation compose(Transformation t);

    //Transformation invert();


    vec3 apply(vec3 point);
    vec4 apply(vec4 point);
    mat4 static rotationMatrix(vec3 v);
};

#endif // TRANSFORMATION_H
