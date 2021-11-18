#include "transformation.h"
//#include "vec3.h"
//#include "object.h"
//#include "entity.h"


    Transformation::Transformation(){translation=vec3();rotation=mat3();scale=vec3(1.0f,1.0f,1.0f);}
    Transformation::Transformation(vec3 trans, mat3 rot, vec3 sc){
        translation=trans;
        rotation=rot;
        scale=sc;
    }
    Transformation Transformation::compose(Transformation t){
        return(Transformation(translation+t.translation,rotation*t.rotation,vec3(scale.x*t.scale.x,scale.y*t.scale.y,scale.z*t.scale.z)));
    }

    Transformation Transformation::invert(){
        if (scale.x*scale.y*scale.z !=0.0){
            return Transformation(translation*(-1),rotation.transpose(),vec3(1.0/scale.x,1.0/scale.y,1.0/scale.z));
        }
        else{return Transformation(translation*(-1),rotation.transpose(),vec3(1.0,1.0,1.0));}
    }


    vec3 Transformation::apply(vec3 point){ //scaling -> rotation -> translation
        vec3 res = vec3(point);

        res.x *= scale.x;
        res.y *= scale.y;
        res.z *= scale.z;

        res = rotation*res;
        res+=translation;
        return res;
    }


