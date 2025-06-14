// GLOBALS //
cbuffer PerFrameBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer PixelBuffer
{
    float4 pixelColor;
};

Texture2D shaderTexture;
SamplerState SampleType;

// TYPEDEFS //
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

// Vertex Shader
PixelInputType FontVertexShader(VertexInputType input)
{
    PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
	// Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
    return output;
}

// Pixel Shader
float4 FontPixelShader(PixelInputType input) : SV_TARGET
{
    float4 color;
	
	// Sample the texture pixel at this location.
    color = shaderTexture.Sample(SampleType, input.tex);
	
	// If the color is black on the texture then treat this pixel as transparent.
    if (color.r == 0.0f)
    {
        discard;
    }
	
	// If the color is other than black on the texture then this is a pixel in the font so draw it using the font pixel color.
    else
    {
        color.rgb = pixelColor.rgb;
        color.a = 1.0f;
    }

    return color;
}
