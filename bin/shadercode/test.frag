#version 330 core
in vec2 pass_uv;
out vec4 FragColor;
uniform float time;

void main()
{
    FragColor = vec4(pass_uv, sin(time) * 0.5 + 0.5, 1.0f);
};
