/** 
 * Texture.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Object.h>

// Windows Direct3D & COM
#include <d3d11_2.h>
#include <wrl.h>

namespace Avalon 
{
	/**
	 * ATexture2D Class
	 *
	 * This class is responsible for creating 2D textures for the game and GPU.
	 *
	 */
	class ATexture2D : public AObject
	{
	private:
		utf16* Filename;
		uint32 Width;
		uint32 Height;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Texture;

	public:
		/**
		 * ATexture2D Constructor
		 *
		 * This default constructor creates and loads a 2D texture in the game and GPU.
		 *
		 * @param const utf8* InFilename: The path to the image file of the texture.
		 *
		 */
		explicit ATexture2D(const utf8* InFilename);

		ID3D11ShaderResourceView* GetTexture(void);

		ID3D11ShaderResourceView** GetTextureAddress(void);

		ID3D11ShaderResourceView *const * GetTextureAddressOf(void);

		void Start(void);

		void Destroy(void);

		void UpdateDimensions(void);

		utf16* GetFilename(void) const;

		/**
		 * ATexture2D GetWidth
		 *
		 * This method returns the width of the selected instance of texture.
		 *
		 * @return uint32: The width of the texture.
		 *
		 */
		uint32 GetWidth(void) const;

		/**
		 * ATexture2D GetHeight
		 *
		 * This method returns the height of the selected instance of the texture.
		 *
		 * @return uint32: The height of the texture.
		 *
		 */
		uint32 GetHeight(void) const;
	};
}