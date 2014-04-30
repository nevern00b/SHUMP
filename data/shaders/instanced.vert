layout(location = POSITION_ATTR) in vec3 aPosition;
layout(location = NORMAL_ATTR) in vec3 aNormal;
layout(location = UV_ATTR) in vec2 aUV;
layout(location = TRANSFORM_ATTR) in vec4 aTransform;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vUV;
out float vNoise;

void main() 
{
	// Calculate transform from translation and 2d angle
	mat4 transform = mat4(1.0);
	transform[0][0] = cos(aTransform.w);
	transform[0][1] = -sin(aTransform.w);
	transform[1][0] = sin(aTransform.w);
	transform[1][1] = cos(aTransform.w);
	transform[3].xyz = aTransform.xyz;

    vec4 position = transform * vec4(aPosition*0.5, 1.0);    
    gl_Position = uPerFrameData.viewProjection * position;
    
    vPosition = vec3(position);
    vNormal = mat3(uTransform.modelMatrix) * aNormal;
    vUV = aUV;
    vNoise = 0.0;
}