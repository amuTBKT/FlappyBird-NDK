attribute vec2 a_position;

uniform mat4 u_cameraMatrix;

varying vec2 v_texCoord;

void main(){
    gl_Position = u_cameraMatrix * vec4(a_position, 0.0, 1.0);
} 