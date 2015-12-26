precision mediump float; 

varying vec2 v_texCoord;
uniform vec4 u_tintColor;
uniform vec4 u_tiling_offset;
uniform float u_transparency;

uniform sampler2D u_diffuseTexture;

void main()
{
	vec2 texCoord = vec2(v_texCoord.x, 1.0 - v_texCoord.y) * u_tiling_offset.xy + u_tiling_offset.zw;
	vec4 diffuseColor = texture2D(u_diffuseTexture, texCoord) * u_tintColor;
	diffuseColor.a *= u_transparency;
	gl_FragColor = diffuseColor;
}