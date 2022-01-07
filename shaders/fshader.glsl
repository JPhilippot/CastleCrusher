#version 420

layout (binding = 0) uniform sampler2D texture0;/*
layout (binding = 1) uniform sampler2D texture1;
layout (binding = 2) uniform sampler2D texture2;
layout (binding = 3) uniform sampler2D texture3;
layout (binding = 4) uniform sampler2D texture4;
layout (binding = 5) uniform sampler2D texture5;
layout (binding = 6) uniform sampler2D texture6;
layout (binding = 7) uniform sampler2D texture7;
layout (binding = 8) uniform sampler2D texture8;*/

in vec2 v_texcoord;
in vec3 v_position;
in float z;
out vec4 color;
//! [0]
void main()
{
    // Set fragment color from texture
    //color = vec3(1.0,z,0.2);
 // if(texture0){

        color = texture2D(texture0,v_texcoord);
//  } else if(texture1){

//      color = texture2D(texture1, v_texcoord);
//} else if(texture2){

//      color = texture2D(texture2, v_texcoord);
//} else if(texture3){

//      color = texture2D(texture3, v_texcoord);
//} else if(texture4){

//      color = texture2D(texture4, v_texcoord);
//} else if(texture5){

//      color = texture2D(texture5, v_texcoord);
//} else if(texture6){

//      color = texture2D(texture6, v_texcoord);
//} else if(texture7){

//      color = texture2D(texture7, v_texcoord);
//} else if(texture8){

//      color = texture2D(texture8, v_texcoord);
//} else

//    color = vec3(1.0,z,0.2,1.0);
//  }

//    }else if (z >= 0.6 && z <0.7){

//        gl_FragColor = texture2D(texture1, v_texcoord);

//    }else {

//        gl_FragColor = texture2D(texture2, v_texcoord);

//
}
//! [0]

