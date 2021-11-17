#version 420

layout (binding = 0) uniform sampler2D texture0;
layout (binding = 1) uniform sampler2D texture1;
layout (binding = 2) uniform sampler2D texture2;

in vec2 v_texcoord;
in vec3 v_position;
in float z;
//! [0]
void main()
{
    // Set fragment color from texture
    if(z < 0.6){

        gl_FragColor = texture2D(texture0, v_texcoord);

    }else if (z >= 0.6 && z <0.7){

        gl_FragColor = texture2D(texture1, v_texcoord);

    }else {

        gl_FragColor = texture2D(texture2, v_texcoord);

    }
}
//! [0]

