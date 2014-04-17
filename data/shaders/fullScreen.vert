layout(location = POSITION_ATTR) in vec2 position;

out vec2 vUV;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
	vUV = position * 0.5 + 0.5; // Go from NDC to window
}
