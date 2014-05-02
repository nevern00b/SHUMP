layout (location = 0) out vec4 fragColor;

uniform sampler2D tColor;
uniform sampler2D tBloom;
uniform sampler2D tBackground;

void main()
{
	vec2 uv = gl_FragCoord.xy*uPerFrameData.invScreenSize;

	vec3 color = vec3(0.0);//texture(tColor, uv).rgb;
	vec3 background = texture(tBackground, uv).rgb;

	vec3 bloom = vec3(0.0);
	//bloom += textureLod(tBloom, uv, 1.0).rgb;
	//bloom += textureLod(tBloom, uv, 2.0).rgb;
	//bloom += textureLod(tBloom, uv, 3.0).rgb;
	vec3 finalColor = color + bloom + background;

    fragColor = vec4(finalColor, 0.0);

}
