layout (location = 0) out vec4 fragColor;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vUV;

//void main()
//{
//	vec4 diffuse = uMaterial.diffuseColor;
//        
//    vec3 viewDir = normalize(vPosition - uPerFrameData.cameraPos);
//	//viewDir += vec3(0.2, 0.0, 0.0);
//    vec3 normal = normalize(vNormal);
//	
//	vec3 finalColor = diffuse.rgb;
//	float specular = max(dot(viewDir, -normal), 0.0);
//	if(specular > 0.98) finalColor = vec3(1.0);
//	if(specular < 0.6) finalColor = vec3(0.0);
//    fragColor = vec4(finalColor, 1.0);
//}



vec3 computeLighting(vec3 viewDir, vec3 lightDir, float lightAttenuation, vec3 lightColor, vec3 diffuse, float specIntensity, float specPower, vec3 normal)
{
    vec3 reflectedLight = reflect(lightDir, normal);
    float diffuseTerm = max(dot(lightDir, normal), 0.0);
    float specularTerm = pow(max(dot(reflectedLight,viewDir), 0.0), specPower);  //phong

	vec3 color = vec3(0.0);
	if(specularTerm > 0.001)
	{
		color = vec3(1.0);
	}

    return color;
}

void main()
{
	vec4 diffuse = uMaterial.diffuseColor;
    vec3 viewDir = normalize(vPosition - uPerFrameData.cameraPos);
    float specIntensity = uMaterial.specIntensity;
    vec3 normal = normalize(vNormal);
        
    vec3 finalColor = diffuse.rgb;
    
	for(int i = 0; i < uLighting.numDirLights; i++)
    {
        DirLightGL dirLight = uLighting.dirLights[i];
        vec3 lightDir = -dirLight.direction;
        vec3 lightColor = dirLight.color;
        float lightAttenuation = 1.0;
        float visibility = 1.0;
        finalColor += visibility * computeLighting(viewDir, lightDir, lightAttenuation, lightColor, diffuse.rgb, specIntensity, uMaterial.specPower, normal);
    }

    for(int i = 0; i < uLighting.numPointLights; i++)
    {
        PointLightGL pointLight = uLighting.pointLights[i];
        
        vec3 lightColor = pointLight.color;        
        vec3 lightDifference =  pointLight.position.rgb - vPosition;
        float lightDistanceSqr = dot(lightDifference, lightDifference);
        vec3 lightDir = lightDifference * inversesqrt(lightDistanceSqr);
		float lightAttenuation = 1.0;
        float visibility = 1.0;
        finalColor += visibility * computeLighting(viewDir, lightDir, lightAttenuation, lightColor, diffuse.rgb, specIntensity, uMaterial.specPower, normal);
    }
	
	float specular = max(dot(viewDir, -normal), 0.0);
	if(specular < 0.6) finalColor = vec3(0.0);

    fragColor = vec4(finalColor, diffuse.a);
}