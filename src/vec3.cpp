
#include "vec3.h"

    vec3::vec3():x(0.0),y(0.0),z(0.0){}

    vec3::vec3(const vec3& copy):x(copy.x),y(copy.y),z(copy.z){}
    vec3::vec3(float x, float y, float z):x(x),y(y),z(z){}
    vec3::vec3(vec3& copy):x(copy.x),y(copy.y),z(copy.z){}

    vec3 vec3::operator +(vec3 const v){return vec3(this->x+v.x,this->y+v.y,this->z+v.z);}
    vec3 vec3::operator -(vec3 const v){return vec3(this->x-v.x,this->y-v.y,this->z-v.z);}
    vec3 vec3::operator *(float const a){return vec3(a*x,a*y,a*z);}
    vec3 vec3::operator /(float const a){return vec3(x/a,y/a,z/a);}

    vec3 vec3::operator +=(vec3 const v){return vec3(x+v.x, y+v.y, z+v.z);}
    vec3 vec3::operator -=(vec3 const v){return vec3(x-v.x, y-v.y, z-v.z);}
    vec3 vec3::operator *=(float const a){return vec3(a*x, a*y, a*z);}
    vec3 vec3::operator /=(float const a){return vec3(x/a, y/a, z/a);}



    float vec3::dot(vec3 const v){return this->x*v.x+this->y*v.y+this->z*v.z;}
    vec3 vec3::cross(vec3 const v){return vec3(y*v.z - z*v.y,  z*v.x - x*v.z, x*v.y - y*v.x);}



    vec2::vec2():x(0.0),y(0.0){}
    vec2::vec2(float x, float y):x(x),y(y){}


    //m00 m01 m02
    //m10 m11 m12
    //m20 m21 m22

    mat3::mat3():m00(1),m01(0),m02(0),m10(0),m11(1),m12(0),m20(0),m21(0),m22(1){}
    mat3::mat3(vec3 a, vec3 b, vec3 c):m00(a.x),m01(b.x), m02(c.x), m10(a.y), m11(b.y),m12(c.y),m20(a.z),m21(b.z),m22(c.z) {}
    mat3::mat3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22):m00(m00),m01(m01),m02(m02),m10(m10),m11(m11),m12(m12),m20(m20),m21(m21),m22(m22){}
    mat3 mat3::zeroes(){return mat3(0,0,0,0,0,0,0,0,0);}

    mat3 mat3::operator*(mat3 const m){return mat3(m00*m.m00+m01*m.m10+m02*m.m20, m00*m.m01+m01*m.m11+m02*m.m21 , m00*m.m02+m01*m.m12+m02*m.m22
                                             ,m10*m.m00+m11*m.m10+m12*m.m20,m10*m.m01+m11*m.m11+m12*m.m21 ,m10*m.m02+m11*m.m12+m12*m.m22
                                             ,m20*m.m00+m21*m.m10+m22*m.m20, m20*m.m01+m21*m.m11+m22*m.m21 , m20*m.m02+m21*m.m12+m22*m.m22 );}

    mat3 mat3::operator+(mat3 const m){return mat3(m00+m.m00,m01+m.m01,m02+m.m02,m10+m.m10, m11+m.m11, m12+m.m12, m20+m.m20, m21+m.m21, m22+m.m22);}

    vec3 mat3::operator *(vec3 const v){
        return vec3(m00,m10,m20)*v.x+vec3(m01,m11,m21)*v.y+vec3(m02,m12,m22)*v.z;
    }

    mat3 mat3::transpose(){
        return mat3(m00,m10,m20,m01,m11,m21,m02,m12,m22);
    }

