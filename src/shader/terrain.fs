#version 410 core
in vec3 fColor;
in vec2 fUV;
in vec3 fNormal;

/* layout(binding = 0) uniform sampler2D heightMap; */
uniform sampler2D heightMap; 

out vec4 color;

float rand(vec2 co)
 {
     return 0.5 + 0.5 *fract(sin( dot(co.xy , vec2(12.9898, 78.233) )) * 43758.5453);
 }
void main()
{
	
    //float colorRes = texture(heightMap, fUV).r;
    //float colorRes = fColor.r;

    //vec3 colorRes = texture(heightMap, fUV).rrr;
    vec3 colorRes = fColor;
    float initColor = colorRes.r;
    if (initColor < 0.2){
    	//float deviation = rand(fUV) / 10;
    	//color = vec4(0.1, 0.1, 0.6 + deviation, 1.0);
    	//color = vec4(0.1, 0.15, 0.75, 1.0) * vec4(texture(heightMap, fUV).rrr, 1.0);
    	color = vec4(0.1, 0.15, 0.8, 1.0) - (vec4(0.0, 0.0, colorRes.r * 2, 0.0) );
    }
    else if (initColor >= 0.199 && initColor < 0.7){
    	//float deviation = rand(fUV) / 10;
    	//color = vec4(0.1, 0.6 + deviation, 0.1 +deviation, 1.0);
    	color =vec4(0.1, 0.6, 0.1, 1.0) * vec4(colorRes.rrr, 1.0);
    }
    else if (initColor >= 0.699 && initColor < 0.9){
    	//float deviation = rand(fUV) / 7;
    	//color = vec4(0.8 + deviation, 0.8 + deviation, 0.8 +deviation, 1.0);
    	color = vec4(0.8, 0.8, 0.8, 1.0) * vec4(colorRes.rrr, 1.0);
    }
    else{
    //float deviation = rand(fUV) / 20;
    //color = vec4(fUV, 0.0, 1.0);
    //color = vec4(0.0, 0.0, 1.0, 1.0);
    
    //color = vec4(1.0 - deviation, 1.0 - deviation, 1.0 - deviation, 1.0);
    color = vec4(1.0, 1.0, 1.0, 1.0) * vec4(colorRes.rrr, 1.0);
    }
    //color = vec4(1.0, 1.0, 1.0, 1.0);
    color = vec4(fColor, 1.0);
    //color = vec4(texture2D(heightMap,fUV), 1.0);
}
