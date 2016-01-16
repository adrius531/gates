#version 410 core
in vec3 vColor;
in vec2 fUV;

/* layout(binding = 0) uniform sampler2D heightMap; */
uniform sampler2D heightMap;

out vec4 color;

void main()
{
	
    color = vec4(texture2D(heightMap, fUV).rrr, 1.0);
    
}
