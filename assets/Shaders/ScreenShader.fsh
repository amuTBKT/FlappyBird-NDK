precision mediump float; 

varying vec2 v_texCoord;

uniform vec2 u_resolution;
uniform vec4 u_tintColor;
uniform vec4 u_tiling_offset;
uniform float u_transparency;

uniform sampler2D u_diffuseTexture;

void main()
{
	vec2 texCoord = v_texCoord * u_tiling_offset.xy + u_tiling_offset.zw;
	vec4 diffuseColor = texture2D(u_diffuseTexture, texCoord) * u_tintColor * u_transparency;
	gl_FragColor = diffuseColor;
}