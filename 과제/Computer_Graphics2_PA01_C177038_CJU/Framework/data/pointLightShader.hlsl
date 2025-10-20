// DEFINES //
#define NUM_LIGHTS 4

// GLOBALS //
cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer CameraBuffer
{
    float3 cameraPosition;
    float padding;
};

cbuffer LightBuffer
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float specularPower;
    float4 specularColor;

};

cbuffer LightPositionBuffer
{
    float4 lightPosition[NUM_LIGHTS];
};

cbuffer LightColorBuffer
{
    float4 diffuseColorPoint[NUM_LIGHTS];
};

Texture2D shaderTexture;
SamplerState SampleType;

// TYPEDEFS //
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    
    float3 viewDirection : TEXCOORD1;
    
    
    
    float3 lightPos1 : TEXCOORD2;
    float3 lightPos2 : TEXCOORD3;
    float3 lightPos3 : TEXCOORD4;
    float3 lightPos4 : TEXCOORD5;
};

// Vertex Shader
PixelInputType LightVertexShader(VertexInputType input)
{
    PixelInputType output;
    float4 worldPosition;


	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
	// Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
	// Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3) worldMatrix);
	
	// Normalize the normal vector.
    output.normal = normalize(output.normal);
	
    // Calculate the position of the vertex in the world.
    worldPosition = mul(input.position, worldMatrix);

    // Determine the light positions based on the position of the lights and the position of the vertex in the world.
    output.lightPos1.xyz = lightPosition[0].xyz - worldPosition.xyz;
    output.lightPos2.xyz = lightPosition[1].xyz - worldPosition.xyz;
    output.lightPos3.xyz = lightPosition[2].xyz - worldPosition.xyz;
    output.lightPos4.xyz = lightPosition[3].xyz - worldPosition.xyz;

    // Normalize the light position vectors.
    output.lightPos1 = normalize(output.lightPos1);
    output.lightPos2 = normalize(output.lightPos2);
    output.lightPos3 = normalize(output.lightPos3);
    output.lightPos4 = normalize(output.lightPos4);
    
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	
    // Normalize the viewing direction vector.
    output.viewDirection = normalize(output.viewDirection);

    return output;
}

// Pixel Shader
float4 LightPixelShader(PixelInputType input) : SV_TARGET
{
    float4 textureColor;
    float3 lightDir;
    float lightIntensity;
    float3 reflection;
    float4 specular;
    
    float lightIntensity1, lightIntensity2, lightIntensity3, lightIntensity4;
    float4 color, color1, color2, color3, color4;
    
    // Ambient base
    color = ambientColor;
    specular = float4(0, 0, 0, 0);

    // ----- Directional Light -----
    lightDir = normalize(-lightDirection);
    lightIntensity = saturate(dot(input.normal, lightDir));

    if (lightIntensity > 0.0f)
    {
        color += diffuseColor * lightIntensity;
        reflection = normalize(2 * lightIntensity * input.normal - lightDir);
        specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower) * specularColor;
    }

    // ----- Point Lights -----
    //float attenuation1 = 1.0f / (1.0f + 0.1f * length(input.lightPos1)); // °¨¼è
    //float attenuation2 = 1.0f / (1.0f + 0.1f * length(input.lightPos2));
    //float attenuation3 = 1.0f / (1.0f + 0.1f * length(input.lightPos3));
    //float attenuation4 = 1.0f / (1.0f + 0.1f * length(input.lightPos4));

    lightIntensity1 = saturate(dot(input.normal, normalize(input.lightPos1)));
    lightIntensity2 = saturate(dot(input.normal, normalize(input.lightPos2)));
    lightIntensity3 = saturate(dot(input.normal, normalize(input.lightPos3)));
    lightIntensity4 = saturate(dot(input.normal, normalize(input.lightPos4)));

    color1 = diffuseColorPoint[0] * lightIntensity1;
    color2 = diffuseColorPoint[1] * lightIntensity2;
    color3 = diffuseColorPoint[2] * lightIntensity3;
    color4 = diffuseColorPoint[3] * lightIntensity4;

    // ----- Combine -----
    textureColor = shaderTexture.Sample(SampleType, input.tex);
    color += saturate(color1 + color2 + color3 + color4);
    color = saturate(color * textureColor + specular);

    return color;
}
