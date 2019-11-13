#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in float mvp_index;

out vec2 fuv;

uniform mat4 MVP[12];

void main(){
    fuv = uv;
    
    gl_Position = MVP[int(mvp_index)] * vec4(vertex, 1);
}
