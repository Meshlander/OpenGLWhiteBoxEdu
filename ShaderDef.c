//v:

#version 430

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 ColorIn;

uniform float GlobalVerts[3];

out vec3 ColorToFragShader;

void main() 
{
	gl_Position = vec4(vp, 1.0);
	ColorToFragShader = ColorIn;
};

//f:

#version 430

out vec4 frag_colour;

uniform float GlobalVerts[3];

in vec3 ColorToFragShader;

void main() 
{
	frag_colour = vec4( 0.002 * gl_FragCoord.x, GlobalVerts[0], 0.9, 1.0) * ColorToFragShader.y;
};

//e: