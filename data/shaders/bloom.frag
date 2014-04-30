layout (location = 0) out vec4 fragColor;

uniform sampler2D tColor;

void main()
{
	vec2 uv = gl_FragCoord.xy*uPerFrameData.invScreenSize;
	vec3 color = texture(tColor, uv).rgb;
    fragColor = vec4(color, 0.0);
}
