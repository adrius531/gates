#version 410 core
layout (location = 0) in vec3 vPosition;
uniform mat4 gVP;

void main()
{

    gl_Position = vec4(vPosition, 1.0);

}
