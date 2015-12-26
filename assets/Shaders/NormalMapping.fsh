precision mediump float; 

varying vec2 v_texCoord;

uniform vec2 u_resolution;
uniform sampler2D u_inputTexture;
uniform sampler2D u_extraTexture;

void main()
{
	vec4 normals = texture2D(u_extraTexture, v_texCoord);
	vec3 normal = normalize(vec3(normals) * 2.0 - vec3(1.0));

	vec2 texCoord = v_texCoord + normal.xy;

	vec4 image = texture2D(u_inputTexture, texCoord);

	gl_FragColor = image;
}