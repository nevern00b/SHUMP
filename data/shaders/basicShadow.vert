layout(location = POSITION_ATTR) in vec3 aPosition;
layout(location = NORMAL_ATTR) in vec3 aNormal;

void main() 
{
	vec3 newPosition = aPosition + 0.1 * aNormal;

    gl_Position = uPerFrameData.shadowMatrix * uTransform.modelMatrix * vec4(newPosition, 1.0);    
}