#version 450 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 aTexCords;

uniform mat4 u_Transform;

out vec2 texCords;

void main()
{
    gl_Position = u_Transform *  aPos;
    texCords = aTexCords;
} 
