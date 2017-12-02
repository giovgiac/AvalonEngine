/**
 * DefaultVertex.hlsl
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

cbuffer TransformBuffer
{
	float4x4 Transform;
};

struct VSOut
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
	float2 TexCoord : TEXCOORD;
};

VSOut main( float4 Position : POSITION, float4 Color : COLOR, float2 TexCoord : TEXCOORD )
{
	// Create Output Struct
	VSOut Output;

	// Configure Output
	Output.Position = mul(Transform, Position);
	Output.Color = Color;
	Output.TexCoord = TexCoord;

	return Output;
}