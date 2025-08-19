#version 450 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCords;

uniform mat4 u_Transform;

out vec2 texCords;

void main()
{
    gl_Position = u_Transform * vec4(aPos.x, aPos.y, 0.0, 1.0);
    texCords = aTexCords;
} 
