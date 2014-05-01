layout (location = 0) out vec4 fragColor;

uniform sampler2D tColor;
uniform sampler2D tBloom;

void main()
{
	vec2 uv = gl_FragCoord.xy*uPerFrameData.invScreenSize;

	vec3 color = texture(tColor, uv).rgb;

	vec3 bloom = vec3(0.0);
	//bloom += textureLod(tBloom, uv, 1.0).rgb;
	bloom += textureLod(tBloom, uv, 2.0).rgb;
	bloom += textureLod(tBloom, uv, 3.0).rgb;
	vec3 finalColor = color + bloom;

    fragColor = vec4(finalColor, 0.0);
}
