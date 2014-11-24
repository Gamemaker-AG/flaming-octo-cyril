#version 330

layout(location = 0) in vec3 vposition;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
uniform mat4 MVP;
out vec2 coord;
out vec3 position;

void main(void)
{
    position = (MVP * vec4(vposition, 1)).xyz;
    coord = texCoord;
    gl_Position = MVP * vec4(vposition, 1.0);
}
