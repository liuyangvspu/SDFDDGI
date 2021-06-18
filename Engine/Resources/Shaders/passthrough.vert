#version 460
#extension GL_ARB_separate_shader_objects : enable


layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;

layout(location = 0) out vec4 o_color;

void main() {
    gl_Position = a_position;
    o_color = a_color;
}