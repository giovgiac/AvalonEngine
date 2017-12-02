/**
 * DefaultPixel.hlsl
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

SamplerState State;
Texture2D Texture;

float4 main( float4 Position : SV_POSITION, float4 Color : COLOR, float2 TexCoord : TEXCOORD ) : SV_TARGET
{
	return Color * Texture.Sample(State, TexCoord);
}