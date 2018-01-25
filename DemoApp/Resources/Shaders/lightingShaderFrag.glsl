#version 330 core

out vec4 FragColour;

//Material
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform float shininess;

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    //For Nvidia (Make sure to declare the same types together)
    float constant;
    float linear;
    float quadratic;

    vec3 position;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//Maximum number of point lights allowed
#define NumOfLights 10

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NumOfLights];

//Function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 result;

void main()
{    
    //Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
	result = vec3(0.0f, 0.0f, 0.0f);

    //Directional lighting
    result += CalcDirLight(dirLight, norm, viewDir);
    //Point lights
    for(int i = 0; i < NumOfLights; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    
    FragColour = vec4(result, 1.0);
}

//Calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    //Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    //Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    //Combine results
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

    return (ambient + diffuse + specular);
}

//Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    //Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    //Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    //Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    //Combine results
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

	//Thank you Juan
	//If the lsit of lights pushed to the shader are less than the maximum defined value
	//Then do not multiply the "empty" lights to the light list
    if(ambient != vec3(0.0f, 0.0f, 0.0f)) {
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
	}

    return (ambient + diffuse + specular);
}