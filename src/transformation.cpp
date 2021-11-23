#include "transformation.h"
#include <iostream>
#include <QtMath>
#include "vec.h"
//#include "object.h"
//#include "entity.h"

mat4 Transformation::rotationMatrix(vec3 v){
    return RotateX(v.x)*RotateY(v.y)*RotateZ(v.z);
}


    Transformation::Transformation(){
        transfo=mat4();
    }
    Transformation::Transformation(vec3 trans, mat4 rot, vec3 sc){
        transfo=Translate(trans)*rot*Scale(sc);
    }

//    Transformation::Transformation(vec3 trans, mat4 rot, vec3 sc, vec3 myrpf){
//        this->rpf=vec3(myrpf);
//        transfo=Translate(trans)*rot*Scale(sc);
//    }

    Transformation::Transformation(mat4 mat){
        transfo=mat;
    }

//    Transformation::Transformation(mat4 mat,vec3 myrpf){
//        rpf=vec3(myrpf);
//        transfo=mat;
//    }


    Transformation Transformation::compose(Transformation t){
        return(Transformation(transfo*t.transfo));
    }

//    Transformation Transformation::invert(){
//        if (scale.x*scale.y*scale.z !=0.0){
//            return Transformation(translation*(-1),transpose(rotation),vec3(1.0/scale.x,1.0/scale.y,1.0/scale.z));
//        }
//        else{return Transformation(translation*(-1),transpose(rotation),vec3(1.0,1.0,1.0));}
//    }

    Transformation::Transformation(vec3 trans, vec3 rot, vec3 sc){
        transfo=Translate(trans)*rotationMatrix(rot)*Scale(sc);
    }

//    Transformation::Transformation(vec3 trans, vec3 rot, vec3 sc,vec3 myrpf){
//        this->rpf=vec3(myrpf);
//        transfo=Translate(trans)*rotationMatrix(rot)*Scale(sc);
//    }


    vec3 Transformation::apply(vec3 point){ //scaling -> rotation -> translation
        vec4 res = vec4(point,1.0);
        return vec3((transfo*res).x,(transfo*res).y,(transfo*res).z);
    }


    vec4 Transformation::apply(vec4 point){ //scaling -> rotation -> translation
        vec4 res = vec4(point);
        return (transfo*res);
    }



