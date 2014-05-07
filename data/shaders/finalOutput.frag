layout (location = 0) out vec4 fragColor;

uniform sampler2D tColor;
uniform sampler2D tBloom;
uniform sampler2D tBackground;

void main()
{
	vec2 uv = gl_FragCoord.xy*uPerFrameData.invScreenSize;

	//vec4 color = texture(tColor, uv);
	//vec3 bloom = texture(tBloom, uv).rgb;

	
	//vec2 offset = noise2(uv.x + uv.y + uPerFrameData.time);
	//vec2 offset = (uv*10.0 - round(uv*10.0))/10.0 + fract(uPerFrameData.time*0.5);
	//uv+= offset;
	vec3 background = texture(tBackground, uv).rgb;
	vec3 finalColor = background;

	//finalColor *= (1.0-color.a);
	//finalColor += color.rgb;
	//finalColor += bloom*0.7;

	// Vignette effect for edge
	vec2 center = vec2(0.5, 0.5);
	float d = distance(uv+vec2(0.0,-0.1), center);
	finalColor *= 1.2-d*2.0;

	// Darken near the end of the tunnel
	//float dc = distance(uv, vec2(0.0, 0.8));
	//finalColor *= -dc

    fragColor = vec4(finalColor, 0.0);
}
