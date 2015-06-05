#version 330

uniform b
{
	mat4 model_matrix;
	mat4 projection_matrix;
 };

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 vs_fs_color;

void main(void)
{
    vs_fs_color = color;
    gl_Position = projection_matrix * (model_matrix * position);
}
