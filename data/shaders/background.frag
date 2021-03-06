layout (location = 0) out vec4 fragColor;

vec2 mod289(vec2 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec3 mod289(vec3 x) {
     return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec3 permute(vec3 x) {
  return mod289(((x*34.0)+1.0)*x);
}

float snoise(vec2 v)
{
      const vec4 C = vec4(0.211324865405187,0.366025403784439,-0.577350269189626,0.024390243902439);
      vec2 i  = floor(v + dot(v, C.yy) );
      vec2 x0 = v -   i + dot(i, C.xx);
      
      vec2 i1;
      i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
      vec4 x12 = x0.xyxy + C.xxzz;
      x12.xy -= i1;
      
      i = mod289(i); // Avoid truncation effects in permutation
      vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 ))
         + i.x + vec3(0.0, i1.x, 1.0 ));
      
      vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
      m = m*m ;
      m = m*m ;
      
      vec3 x = 2.0 * fract(p * C.www) - 1.0;
      vec3 h = abs(x) - 0.5;
      vec3 ox = floor(x + 0.5);
      vec3 a0 = x - ox;
      
      m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );
      
      vec3 g;
      g.x  = a0.x  * x0.x  + h.x  * x0.y;
      g.yz = a0.yz * x12.xz + h.yz * x12.yw;

      return 105.0 * dot(m, g);      
}

float fbm(vec2 p) {
    float f = 0.0;
	float t = fract(uPerFrameData.time*0.5);
    float w = abs(0.5-t*t)*0.8+0.2;

    //Controls rate of noise. Omit GlobalTime param for constant noise level of tunnel
    f += w * snoise(p*5.0); //5.0 changes intensity

    p *= 2.;
    w *= 0.5;

    return 2.0*f;
}


vec4 tunneliter(vec2 texCoord,vec4 incol,float cx,float cy,float limita,float limitb,vec4 coloz,float tadd)
{
    vec2 texc;
    vec2 tex;
    vec4 outCol;
    float disty;
    
    texc=(texCoord-vec2(cx,cy));
	//float t = fract(uPerFrameData.time*0.5);
	//float vary = abs(0.5-t)/3.0 - 0.1;
    disty= 10.0 * distance(texc,vec2(0.0,0.0)); // Changing 5.0 makes it go faster or slower
    tex.x=(abs(atan(texc.x,texc.y)))/6.2830;
    tex.y=0.5/disty;  
    tex.y+=(uPerFrameData.time*0.9)+tadd;

    float fbmval=abs(fbm(tex)); 

	float bex=mix(fbmval,1.0,smoothstep(limitb,limita,disty))*smoothstep(limitb,limita,disty);
    outCol=mix(incol,coloz*(1.0-fbmval),bex);
            
    return 0.5*outCol;
} 

void main()
{
    fragColor = vec4(1.0);
	vec2 uv = gl_FragCoord.xy * uPerFrameData.invBackgroundSize;
	float time = uPerFrameData.time;
	fragColor = vec4(uv,0.5+0.5*sin(time),1.0);

    vec4 finalCol;
    
    //float xa=(sin(time)*0.000004)+(sin((time*1.3)+0.5)*0.00000024);
	//float ya=(cos(time)*0.45)+(cos((time*0.6)-0.7)*0.3);

	float xa=0.0;
	float ya=0.0;

    finalCol=vec4(0.0,0.0,0.0,1.0);
    //finalCol=tunneliter(uv,finalCol,0.5+(xa*0.80),0.85+(ya*0.80),0.01,0.9,vec4(0.1,0.3,0.2,1.0),9.1);    
    finalCol=tunneliter(uv,vec4(0.0,0.0,0.0,1.0),0.5+(xa*0.70),0.85+(ya*0.70),0.4,0.05,vec4(1.0,1.0,1.0,1.0),9.3);   

	
	if(finalCol.r > 0.45)
	{
		float r = (finalCol.r-0.45);
		float value = 0.45 + sqrt(r);
		finalCol = vec4(value, value, value, 1.0);
	}
	

	finalCol.rgb *= uPerFrameData.backgroundColor;

    fragColor = vec4(finalCol.xyz, 1.0);
}