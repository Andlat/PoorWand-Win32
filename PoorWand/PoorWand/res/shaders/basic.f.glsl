#version 330 core

in vec2 fuv;
uniform sampler2D tex;

out vec4 color;

void main(){
    color = texture(tex, fuv);//vec4(255, 255, 255, 1);
}
