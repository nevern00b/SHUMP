out vec4 fragColor;
in vec2 vUV;

uniform sampler2D tColor;

void main()
{
	vec3 color = texture(tColor, vUV).rgb;
    fragColor = vec4(color, 0.0);
}
