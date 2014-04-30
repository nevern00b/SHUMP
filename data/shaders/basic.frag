layout (location = 0) out vec4 fragColor;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vUV;
in float vNoise;

uniform sampler2D tDiffuse;
uniform sampler2D tNormal;
uniform sampler2D tSpecular;
uniform samplerCube tReflect;

#define AMBIENT_TERM 0.5

vec3 computeLighting(vec3 viewDir, vec3 lightDir, float lightAttenuation, vec3 lightColor, vec3 diffuse, float specIntensity, float specPower, vec3 normal)
{
    vec3 reflectedLight = reflect(lightDir, normal);
    float diffuseTerm = max(dot(lightDir, normal), 0.0);
    float specularTerm = pow(max(dot(reflectedLight,viewDir), 0.0), specPower);  //phong

    vec3 color = (lightColor * lightAttenuation) * (diffuse * diffuseTerm + vec3(specIntensity * specularTerm));
    return color;
}

mat3 getTangentMatrix(vec3 N, vec3 p, vec2 uv)
{
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );
 
    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
 
    // construct a scale-invariant frame 
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

void main()
{
	vec4 diffuse = uMaterial.diffuseColor;
	if(uMaterial.noiseStrength > 0.01) diffuse.rgb *= vNoise;
    if(uMaterial.diffuseBlend > 0.0)
    {
        vec4 diffuseTexture = texture(tDiffuse, vUV);
        diffuse = mix(diffuse, diffuseTexture, uMaterial.diffuseBlend); 
    }
    
    if(diffuse.a < 0.1) discard; // For alpha cutout
    
    vec3 viewDir = normalize(vPosition - uPerFrameData.cameraPos);
    
    float specIntensity = uMaterial.specIntensity;
    if(uMaterial.specBlend > 0.0)
    {    
        float specIntensityTexture = texture(tSpecular, vUV).a;
        specIntensity = mix(specIntensity, specIntensityTexture, uMaterial.specBlend);
    }
    
    float normalDirection = float(gl_FrontFacing) * 2.0 - 1.0; // If back facing, the normal will be negated (useful for alpha cutout)
    vec3 normal = normalize(vNormal) * normalDirection;
    
    if(uMaterial.normalIntensity > 0.0)
    {
        vec3 mapNormal = texture(tNormal, vUV).rgb;
        mapNormal = mapNormal * 255./127. - 128./127.; // Unsigned to Signed: 0.5 can't be represented in unsigned texture format, so do this to compensate
        mapNormal.y = -mapNormal.y; // Do this if normal map is green up
        mapNormal = mix(vec3(0, 0, 1), mapNormal, uMaterial.normalIntensity);
        mat3 tangentMatrix = getTangentMatrix(normal, viewDir, vUV);
        normal = normalize(tangentMatrix * mapNormal);
    }
        
    if(uMaterial.reflectBlend > 0.0)
    {
        vec3 reflectDir = reflect(viewDir, normal);
        vec4 reflectTexture = texture(tReflect, reflectDir);
        diffuse = mix(diffuse, reflectTexture, uMaterial.reflectBlend);
    }
        
    vec3 finalColor = diffuse.rgb * AMBIENT_TERM;
    
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
        
        float lightAttenuation = max(0.0, 1.0 - lightDistanceSqr*pointLight.position.a);
        lightAttenuation *= lightAttenuation;
        
        float visibility = 1.0;
        finalColor += visibility * computeLighting(viewDir, lightDir, lightAttenuation, lightColor, diffuse.rgb, specIntensity, uMaterial.specPower, normal);
    }
	
    fragColor = vec4(finalColor, diffuse.a);
}
