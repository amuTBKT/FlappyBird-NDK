precision mediump float; 

varying vec2 v_texCoord;

uniform vec2 u_resolution;
uniform sampler2D u_inputTexture;

const float cellSize = 0.01;

void main()
{
	vec4 image = vec4(0);
	
	float startX = floor(v_texCoord.x * (1.0 / cellSize)) / (1.0 / cellSize);
	float startY = floor(v_texCoord.y * (1.0 / cellSize)) / (1.0 / cellSize);
	float draws = 0;

	for (float y = 0; y < cellSize; y += cellSize / 10.0){
		for (float x = 0; x < cellSize; x += cellSize / 10.0){
			image += texture2D(u_inputTexture, vec2(startX, startY) + vec2(x, y));
			draws++;
		}	
	}
	image /= draws;

	gl_FragColor = image;
}



/*int pass = 0;
float start = -0.05;
float end = 0.05;
float step = 0.025;

for (float x = start; x <= end; x += step){
	for (float y = start; y <= end; y += step){
		image += texture2D(u_inputTexture, v_texCoord + vec2(x, y));
		pass++;
	}
}
image /= pass;*/