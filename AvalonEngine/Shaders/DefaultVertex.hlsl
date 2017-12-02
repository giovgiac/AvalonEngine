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
};

VSOut main( float4 Position : POSITION, float4 Color : COLOR )
{
	// Create Output Struct
	VSOut Output;

	// Configure Output
	Output.Position = mul(Transform, Position);
	Output.Color = Color;

	return Output;
}