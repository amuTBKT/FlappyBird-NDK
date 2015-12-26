precision mediump float; 

varying vec2 v_texCoord;

uniform vec4 u_color;
uniform sampler2D u_diffuseTexture;

void main(){
	vec4 diffuseColor = texture2D(u_diffuseTexture, v_texCoord) * u_color;
	gl_FragColor = diffuseColor;
}