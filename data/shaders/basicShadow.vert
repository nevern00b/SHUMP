layout(location = POSITION_ATTR) in vec3 aPosition;

void main() 
{
    gl_Position = uPerFrameData.shadowMatrix * uTransform.modelMatrix * vec4(aPosition, 1.0);    
}