#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 2) in vec2 textCord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    //    gl_Position = vec4(pos, 1.0) * model * view * projection;
    gl_Position =projection * view * model *  vec4(pos, 1.0);
    TexCoord = vec2(textCord.x, 1.0 - textCord.y);
}

