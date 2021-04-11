#type vertex

#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_Transform;

out vec4 v_Color;

void main()
{ 	
	gl_Position = u_Transform * vec4(a_Position, 1.0f);
	v_Color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

#type fragment

#version 330 core
			
layout(location = 0) out vec4 color;
in vec4 v_Color;
void main()
{
	color = v_Color;
}