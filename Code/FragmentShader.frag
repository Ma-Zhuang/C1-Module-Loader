#version 330 core

in vec2 TextCoord;
in vec3 fragPos;
in vec3 aNormal;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct LightDirectional{
	vec3 pos;
	vec3 color;
	vec3 dirToLigth;
};

uniform LightDirectional lightD;
uniform Material material;

uniform sampler2D tex;
uniform vec3 objColor;
//Environmental color
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform vec3 lightDirUniform;
out vec4 color;

//With texture map
vec3 CalcLightDirectional(LightDirectional light,vec3 uNormal,vec3 dirToCamers){
	
	//diffuse
	float diffIntensity = max(dot(light.dirToLigth, uNormal), 0);
	vec3 diffColor = diffIntensity * light.color * texture2D(tex,TextCoord).rgb * ambientColor;
	
	//specular
	vec3 R=normalize(reflect(-light.dirToLigth,uNormal));
	float specIntensity = pow( max(dot(R, dirToCamers),0) ,material.shininess);
	vec3 specColor = specIntensity * light.color * texture2D(tex,TextCoord).rgb * ambientColor;

	vec3 result=diffColor + specColor;
	return result;
}

//No texture map
vec3 CalcLightDirectionalnt(LightDirectional light,vec3 uNormal,vec3 dirToCamers){
	
	//diffuse
	float diffIntensity = max(dot(light.dirToLigth, uNormal), 0);
	vec3 diffColor = diffIntensity * light.color * material.diffuse * ambientColor;
	
	//specular
	vec3 R=normalize(reflect(-light.dirToLigth,uNormal));
	float specIntensity = pow( max(dot(R, dirToCamers),0) ,material.shininess);
	vec3 specColor = specIntensity * light.color * material.specular * ambientColor;

	vec3 result=diffColor + specColor;
	return result;
}
void main()
{
	float hastexture;
	hastexture+=texture2D(tex,TextCoord).x;
	hastexture+=texture2D(tex,TextCoord).y;
	hastexture+=texture2D(tex,TextCoord).z;
	vec3 finalResulr=vec3(0,0,0);
	vec3 uNormal=normalize(aNormal);
	vec3 firToCamera=normalize(cameraPos-fragPos);
	if(hastexture > 0){
		finalResulr+=CalcLightDirectional(lightD,uNormal,firToCamera);
	}
	else {
		finalResulr+=CalcLightDirectionalnt(lightD,uNormal,firToCamera);
	}
	color = vec4(finalResulr,1.0);
}