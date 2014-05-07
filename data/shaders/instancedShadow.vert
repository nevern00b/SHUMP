layout(location = POSITION_ATTR) in vec3 aPosition;
layout(location = TRANSFORM_ATTR) in vec4 aTransform;

void main() 
{
    vec4 position = vec4(aTransform.xyz + aPosition*0.5, 1.0);    
    gl_Position = uPerFrameData.shadowMatrix * position;

	//vec4 position = vec4(aTransform.xyz + aPosition*0.5 + vec3(0.0,0.0,-2.0), 1.0);    
    //gl_Position = uPerFrameData.viewProjection * position;
}
