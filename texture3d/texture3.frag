#version 150

in vec3 UV;
out vec4 color_out;
uniform sampler3D textureSampler;


void main()
{
	color_out = texture(textureSampler, UV).rgba;
	//color_out = vec4(0.0,1.0,0.0,1.0);
}