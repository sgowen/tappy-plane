struct VOut
{
	float4 position : SV_POSITION;
	float2 texcoord: TEXCOORD;        // texture coordinates
};

// Vertex Shader
VOut main(float4 position : POSITION)
{
	// create a VOut struct
	VOut output;

	// set the output values
	output.position = position;    // pass through (assuming position is in screen coordinates of -1 to 1)
	output.texcoord = (position + 1.0) / 2.0;
	output.texcoord.y = 1 - output.texcoord.y;

	// return the output values
	return output;
}