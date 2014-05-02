layout (location = 0) out vec4 fragColor;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vUV;
in float vNoise;

void main()
{
	vec3 color = vec3(0.0);
	float value = fract(fract(vUV.y + uPerFrameData.time*0.1)*10.0);
	if(value < 0.05)
	{
		color = value * vec3(1.0)*10.0;
	}
	else 
	{
		discard;
	}
    fragColor = vec4(color, 1.0);
}
