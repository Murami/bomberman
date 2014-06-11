#version 120

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;

uniform sampler2D fTexture0;

varying vec4 fColor;
varying vec4 fNormal;
varying vec2 fUv;

void main(void)
{
	vec2 uv = fUv;
	uv.x = mod(uv.x, 1.00);
	uv.y = mod(uv.y, 1.00);
	gl_FragColor = texture2D(fTexture0, uv) * fColor;
}
