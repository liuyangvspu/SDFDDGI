#version 460
#extension GL_ARB_separate_shader_objects : enable


//layout(location = 0) in vec4 o_color;

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
//    FragColor = o_color;
} 
