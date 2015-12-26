precision mediump float; 

varying vec2 v_texCoord;

uniform vec2 u_resolution;
uniform sampler2D u_inputTexture;

void main()
{
	vec4 image = texture2D(u_inputTexture, v_texCoord);
	float gray = (image.r + image.g + image.b) / 3.0;
	gl_FragColor = vec4(gray, gray, gray, image.a);
}