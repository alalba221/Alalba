#type vertex
#version 430

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 TexCoord;
void main()
{

	gl_Position = vec4(a_Position, 1.0);

	TexCoord = a_TexCoord;
}

#type fragment
#version 430

out vec4 finalColor;
in vec2 TexCoord;

uniform sampler2D u_Texture;
void main()
{
	//finalColor = texture(u_Texture,TexCoord);
	/// Gamma correct
	const float gamma = 2.2;
    vec3 hdrColor = texture(u_Texture, TexCoord).rgb;
	finalColor = vec4(pow(hdrColor, vec3(1.0 / gamma)),1.0);

	/// Tone mapping
//	vec3 mapped = vec3(1.0) - exp(-hdrColor * 0.1);
//	mapped = pow(mapped, vec3(1.0 / gamma));
//	finalColor = vec4(mapped, 1.0);
  
}
