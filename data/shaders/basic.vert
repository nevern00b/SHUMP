layout(location = POSITION_ATTR) in vec3 aPosition;
layout(location = NORMAL_ATTR) in vec3 aNormal;
layout(location = UV_ATTR) in vec2 aUV;

out block
{
    vec3 position;
    vec3 normal;
    vec2 uv;
} vertexData;

void main() 
{
    vec4 position = uTransform.modelMatrix * vec4(aPosition, 1.0);    
    gl_Position = uPerFrameData.viewProjection * position;
    
    vertexData.position = vec3(position);
    vertexData.normal = mat3(uTransform.modelMatrix) * aNormal;
    vertexData.uv = aUV;
}