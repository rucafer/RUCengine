#type vertex

#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec2 v_TexCoord;
out vec3 v_Color;

void main()
{ 	
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
	v_TexCoord = a_TexCoord;
	v_Color = vec3(u_ViewProjection[1][0], u_ViewProjection[1][1], u_ViewProjection[1][2]);
}

#type fragment

#version 330 core
			
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Color;

uniform sampler2D u_Texture;

void main()
{
	color = vec4(v_Color, 1.0f);
	//color = texture(u_Texture, v_TexCoord);
}