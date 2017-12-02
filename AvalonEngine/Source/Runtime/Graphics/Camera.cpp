/**
 * Camera.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Camera.h"

#include <Core/Config.h>

namespace Avalon 
{
	ACamera::ACamera(void)
		: 
		Left(0.0f),
		Right(0.0f),
		Bottom(0.0f),
		Top(0.0f),
		Near(DefaultCameraNear),
		Far(DefaultCameraFar),
		Eye(0.0f, 0.0f, -0.5f),
		Focus(0.0f, 0.0f, 0.0f),
		Up(0.0f, 1.0f, 0.0f)
	{
	
	}

	ACamera::ACamera(const float InRight, const float InTop)
		: 
		Left(-InRight / 2.0f),
		Right(InRight / 2.0f),
		Bottom(-InTop / 2.0f),
		Top(InTop / 2.0f),
		Near(DefaultCameraNear),
		Far(DefaultCameraFar),
		Eye(0.0f, 0.0f, -0.5f),
		Focus(0.0f, 0.0f, 0.0f),
		Up(0.0f, 1.0f, 0.0f)
	{
	
	}

	ACamera::ACamera(const float InLeft, const float InRight, const float InBottom, const float InTop, const float InNear, const float InFar)
		: 
		Left(InLeft),
		Right(InRight),
		Bottom(InBottom),
		Top(InTop),
		Near(InNear),
		Far(InFar),
		Eye(0.0f, 0.0f, -0.5f),
		Focus(0.0f, 0.0f, 0.0f),
		Up(0.0f, 1.0f, 0.0f)
	{
		
	}

	void ACamera::SetCamera(const float InLeft, const float InRight, const float InBottom, const float InTop, const float InNear, const float InFar) 
	{
		Left = InLeft;
		Right = InRight;
		Bottom = InBottom;
		Top = InTop;
		Near = InNear;
		Far = InFar;
	}

	XMMATRIX ACamera::GetView(void) const
	{
		XMVECTOR EyeVector = XMLoadFloat3(&Eye);
		XMVECTOR FocusVector = XMLoadFloat3(&Focus);
		XMVECTOR UpVector = XMLoadFloat3(&Up);

		return XMMatrixLookAtLH(EyeVector, FocusVector, UpVector);
	}

	XMMATRIX ACamera::GetProjection(void) const
	{
		return XMMatrixOrthographicOffCenterLH(Left, Right, Bottom, Top, Near, Far);
	}
}