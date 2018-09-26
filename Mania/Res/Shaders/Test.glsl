#vertex
#version 330

layout(location = 0) in vec2 pos;

uniform mat4 Projection;

uniform vec2 Pos;
uniform vec2 Size;

out vec2 texCoord0;

void main()
{
	mat4 t = mat4(1.0, 0.0, 0.0, 0.0,
				  0.0, 1.0, 0.0, 0.0,
				  0.0, 0.0, 1.0, 0.0,
				  Pos.x, Pos.y, 0.0, 1.0);

	mat4 s = mat4(Size.x, 0.0, 0.0, 0.0,
				  0.0, Size.y, 0.0, 0.0,
				  0.0, 0.0, 1.0, 0.0,
				  0.0, 0.0, 0.0, 1.0);

	mat4 transform = t * s;

	gl_Position = Projection * transform * vec4(pos, 1.0, 1.0);

	texCoord0 = pos;
}

#fragment
#version 330

in vec2 texCoord0;

out vec4 outColor;

uniform vec4 Color;
uniform sampler2D Texture;
uniform int HasTexture;

void main()
{
	outColor = Color;
	if( HasTexture == 1 )
		outColor = outColor * texture(Texture, texCoord0);
}