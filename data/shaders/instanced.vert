layout(location = POSITION_ATTR) in vec3 aPosition;
layout(location = NORMAL_ATTR) in vec3 aNormal;
layout(location = UV_ATTR) in vec2 aUV;
layout(location = TRANSFORM_ATTR) in vec4 aTransform;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vUV;

void main() 
{
	// Calculate transform from translation and 2d angle
	//float angle = uPerFrameData.time*20.0f;

	//mat3 transform = mat3(1.0);
	//transform[0][0] = cos(angle);
	//transform[0][1] = -sin(angle);
	//transform[1][0] = sin(angle);
	//transform[1][1] = cos(angle);

    vec4 position = vec4(aTransform.xyz + aPosition*0.5, 1.0);    
    gl_Position = uPerFrameData.viewProjection * position;
    
    vPosition = vec3(position);
    vNormal = aNormal;
    vUV = aUV;
}