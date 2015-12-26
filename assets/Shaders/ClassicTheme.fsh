precision mediump float; 

varying vec2 v_texCoord;

uniform vec2 u_resolution;
uniform sampler2D u_inputTexture;

uniform sampler2D u_extraTexture;
uniform vec2 u_trackingPosition;
uniform float u_radius; 

// noise generator
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec2 texCoord = v_texCoord;
	
	// distorting the image using noise
	float strength = 0.0025;
	//texCoord += -2.0 * strength + strength * vec2(rand(v_texCoord), rand(v_texCoord));
	vec4 image = texture2D(u_inputTexture, texCoord);

	// adding radial gradient
	vec2 pixelCoord = gl_FragCoord.xy;
	float distance = distance(pixelCoord, u_trackingPosition);
	image *= mix(0.7, 1.0, exp(-distance / u_radius));				// for subtle gradient near the center 

	// adding noise to image
	vec2 randomSeed = texCoord;
	image.r *= clamp(rand(randomSeed + image.rr), 0.8, 1.0);
	image.g *= clamp(rand(randomSeed + image.gg), 0.8, 1.0);
	image.b *= clamp(rand(randomSeed + image.bb), 0.8, 1.0);
	
	gl_FragColor = image;
}