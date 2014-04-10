layout(location = POSITION_ATTR) in vec3 aPosition;
layout(location = NORMAL_ATTR) in vec3 aNormal;
layout(location = UV_ATTR) in vec2 aUV;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vUV;

void main() 
{
    vec4 position = uTransform.modelMatrix * vec4(aPosition, 1.0);    
    gl_Position = uPerFrameData.viewProjection * position;
    
    vPosition = vec3(position);
    vNormal = mat3(uTransform.modelMatrix) * aNormal;
    vUV = aUV;
}