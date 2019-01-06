#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in float mvp_index;

uniform mat4 MVP[2];

void main(){
    int g = int(1.f);//int(mvp_index);
    vec3 o = vec3(vertex.x, vertex.y, vertex.z+g);
    gl_Position = MVP[g] * vec4(o, 1);
}
