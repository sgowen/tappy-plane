cbuffer ConstantBuffer
{
	float4x4 matFinal;
}

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord: TEXCOORD;        // texture coordinates
};

// Vertex Shader
VOut main(float4 position : POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD)
{
	// create a VOut struct
	VOut output;

	// set the output values
	output.position = mul(matFinal, position);    // transform the vertex from 3D to 2D
	output.color = color;
	output.texcoord = texcoord;    // set the texture coordinates, unmodified

	// return the output values
	return output;
}