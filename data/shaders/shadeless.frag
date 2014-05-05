layout (location = 0) out vec4 fragColor;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vUV;

void main()
{
	vec4 diffuse = uMaterial.diffuseColor;
        
    vec3 viewDir = normalize(vPosition - uPerFrameData.cameraPos);
	//viewDir += vec3(0.2, 0.0, 0.0);
    vec3 normal = normalize(vNormal);
	
	vec3 finalColor = diffuse.rgb;
	float specular = max(dot(viewDir, -normal), 0.0);
	if(specular > 0.98) finalColor = vec3(1.0);
	if(specular < 0.6) finalColor = vec3(0.0);
    fragColor = vec4(finalColor, 1.0);
}
