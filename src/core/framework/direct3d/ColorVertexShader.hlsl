cbuffer ConstantBuffer
{
	float4x4 matFinal;
}

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

// Vertex Shader
VOut main(float4 position : POSITION, float4 color : COLOR)
{
	// create a VOut struct
	VOut output;

	// set the output values
	output.position = mul(matFinal, position);    // transform the vertex from 3D to 2D
	output.color = color;

	// return the output values
	return output;
}