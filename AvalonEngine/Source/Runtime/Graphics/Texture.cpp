/**
 * Texture.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Texture.h"

namespace Avalon {
	ATexture2D::ATexture2D(const utf8* InFilename)
	{
		uint64 Length = strlen(InFilename);

		// Copy And Convert Filename To UTF-16
		Filename = new utf16[Length + 1];
		mbstowcs_s(&Length, Filename, Length + 1, InFilename, Length);
	}

	void ATexture2D::Start(void)
	{

	}

	void ATexture2D::Destroy(void)
	{
		if (Filename)
		{
			delete Filename;
		}
	}

	void ATexture2D::UpdateDimensions(void)
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> TextureInterface = nullptr;
		Microsoft::WRL::ComPtr<ID3D11Resource> TextureResource = nullptr;
		
		Texture->GetResource(&TextureResource);
		TextureResource.As(&TextureInterface);

		D3D11_TEXTURE2D_DESC TextureDesc = { 0 };
		TextureInterface->GetDesc(&TextureDesc);

		// Update Width and Height
		Width = TextureDesc.Width;
		Height = TextureDesc.Height;
	}

	ID3D11ShaderResourceView* ATexture2D::GetTexture(void)
	{
		return Texture.Get();
	}

	ID3D11ShaderResourceView** ATexture2D::GetTextureAddress(void)
	{
		return &Texture;
	}

	ID3D11ShaderResourceView *const * ATexture2D::GetTextureAddressOf(void)
	{
		return Texture.GetAddressOf();
	}

	utf16* ATexture2D::GetFilename(void) const
	{
		return Filename;
	}

	uint32 ATexture2D::GetWidth(void) const 
	{ 
		return Width;
	}

	uint32 ATexture2D::GetHeight(void) const 
	{
		return Height;
	}
}