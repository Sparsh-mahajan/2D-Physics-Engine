#shader vertex
#version 330 core

layout(location = 0) in vec4 Position;

void main()
{
   gl_Position = Position;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 Color;

void main()
{
   Color = vec4(1.0, 0.4, 0.7, 1.0);
};