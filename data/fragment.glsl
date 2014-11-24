#version 330
in vec2 coord;
in vec3 position;

out vec4 fragColor;
void main(void)
{
    fragColor = vec4(coord.y, coord.x, position.z,1);
}

