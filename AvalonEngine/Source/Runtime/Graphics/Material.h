/**
 * Material.h
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
	class AMaterial : public AObject
	{
	private:
		class ATexture2D* Diffuse;
		utf8* PixelFilename;
		utf8* VertexFilename;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayout;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;

	public:
		AMaterial(void);

		AMaterial(class ATexture2D* InDiffuse);

		AMaterial(class ATexture2D* InDiffuse, const utf8* InPixelFilename, const utf8* InVertexFilename);

		void Destroy(void);

		void Start(void);

		utf8* GetPixelFilename(void) const;

		utf8* GetVertexFilename(void) const;

		ID3D11InputLayout* GetInputLayout(void);

		ID3D11PixelShader* GetPixelShader(void);

		ID3D11VertexShader* GetVertexShader(void);

		ID3D11InputLayout** GetInputLayoutAddress(void);

		ID3D11PixelShader** GetPixelShaderAddress(void);

		ID3D11VertexShader** GetVertexShaderAddress(void);
	};
}