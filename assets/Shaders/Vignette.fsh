precision mediump float; 

varying vec2 v_texCoord;

uniform vec2 u_resolution;

uniform sampler2D u_inputTexture;

const float outerRadius = 1.4, innerRadius = 0.5, intensity = 0.5;
const vec3 tintColor = vec3(238.0 / 255.0, 234.0 / 255.0, 112.0 / 255.0);

void main()
{
	vec2 texCoord =  v_texCoord;
	vec4 image = texture2D(u_inputTexture, v_texCoord);

	float len = length(gl_FragCoord.xy / u_resolution - 0.5);
	float vignette = smoothstep(outerRadius, innerRadius, len);
	image = mix(image, image * vignette, intensity);

	image.rgb = mix(image.rgb, image.rgb * tintColor, 0.5);

	gl_FragColor = image;
}