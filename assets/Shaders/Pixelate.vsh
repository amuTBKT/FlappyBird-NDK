attribute vec2 a_position;
attribute vec2 a_texCoord;

uniform mat4 u_modelMatrix;
uniform mat4 u_cameraMatrix;

varying vec2 v_texCoord;

void main()
{
	v_texCoord = a_texCoord;
    gl_Position = u_cameraMatrix * u_modelMatrix * vec4(a_position, 0, 1);
} 