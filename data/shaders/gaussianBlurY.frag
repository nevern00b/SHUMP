layout (location = 0) out vec4 fragColor;

uniform sampler2D tBlur;

uniform float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
uniform float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );

void main(void)
{
	fragColor = texture(tBlur, gl_FragCoord.xy*uPerFrameData.invScreenSize) * weight[0];
	for (int i=1; i<3; i++) 
	{
		fragColor += texture(tBlur, (gl_FragCoord.xy + vec2(0.0, offset[i]))*uPerFrameData.invScreenSize) * weight[i];
		fragColor += texture(tBlur, (gl_FragCoord.xy - vec2(0.0, offset[i]))*uPerFrameData.invScreenSize) * weight[i];
	}
}
