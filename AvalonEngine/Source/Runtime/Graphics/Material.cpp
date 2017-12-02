/**
 * Material.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Material.h"

#include <Core/Config.h>

#include <Graphics/Texture.h>

#include <Utils/File.h>

namespace Avalon
{
	AMaterial::AMaterial(void)
		: 
		Diffuse(nullptr),
		PixelFilename(_strdup(DefaultFragmentFilename)),
		VertexFilename(_strdup(DefaultVertexFilename))
	{
		
	}

	AMaterial::AMaterial(ATexture2D* InDiffuse)
		:
		Diffuse(InDiffuse),
		PixelFilename(_strdup(DefaultFragmentFilename)),
		VertexFilename(_strdup(DefaultVertexFilename))
	{

	}

	AMaterial::AMaterial(class ATexture2D* InDiffuse, const utf8* InPixelFilename, const utf8* InVertexFilename)
		:
		Diffuse(InDiffuse),
		PixelFilename(_strdup(InPixelFilename)),
		VertexFilename(_strdup(InVertexFilename))
	{

	}

	void AMaterial::Destroy(void)
	{
		if (Diffuse)
		{
			Diffuse->Destroy();
			delete Diffuse;
		}

		if (PixelFilename)
		{
			delete PixelFilename;
		}

		if (VertexFilename)
		{
			delete VertexFilename;
		}
	}

	void AMaterial::Start(void)
	{

	}

	void AMaterial::SetDiffuse(ATexture2D* InDiffuse)
	{
		Diffuse = InDiffuse;
	}

	ATexture2D* AMaterial::GetDiffuse(void) const
	{
		return Diffuse;
	}

	utf8* AMaterial::GetPixelFilename(void) const
	{
		return PixelFilename;
	}

	utf8* AMaterial::GetVertexFilename(void) const
	{
		return VertexFilename;
	}

	ID3D11InputLayout* AMaterial::GetInputLayout(void)
	{
		return InputLayout.Get();
	}

	ID3D11PixelShader* AMaterial::GetPixelShader(void)
	{
		return PixelShader.Get();
	}

	ID3D11VertexShader* AMaterial::GetVertexShader(void)
	{
		return VertexShader.Get();
	}

	ID3D11InputLayout** AMaterial::GetInputLayoutAddress(void)
	{
		return &InputLayout;
	}

	ID3D11PixelShader** AMaterial::GetPixelShaderAddress(void)
	{
		return &PixelShader;
	}

	ID3D11VertexShader** AMaterial::GetVertexShaderAddress(void) 
	{
		return &VertexShader;
	}
}