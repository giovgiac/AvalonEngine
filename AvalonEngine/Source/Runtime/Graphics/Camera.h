/**
 * Camera.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Actors/Actor.h>

namespace Avalon 
{
	/**
	 * ACamera Class
	 *
	 * This class is responsible for creating and managing the virtual camera in the world.
	 *
	 */
	class ACamera : public AActor
	{
	protected:
		float Left;
		float Right;
		float Bottom;
		float Top;
		float Near;
		float Far;

		XMFLOAT3 Eye;
		XMFLOAT3 Focus;
		XMFLOAT3 Up;

	public:
		/**
		 * ACamera Constructor
		 *
		 * This default constructor initializes the camera to the default configuration values.
		 *
		 */
		ACamera(void);

		/**
		 * ACamera Constructor
		 *
		 * This constructor initializes the camera with the given left, right, bottom and top planes and uses the near and far from the default configuration.
		 *
		 * @param const float InRight: The value to clip the camera at the right.
		 * @param const float InTop: The value to clip the camera at the top.
		 *
		 */
		ACamera(const float InRight, const float InTop);

		/**
		 * ACamera Constructor
		 *
		 * This constructor initializes the camera with the given left, right, bottom, top, near and far planes.
		 *
		 * @param const float InLeft: The value to clip the camera at the left.
		 * @param const float InRight: The value to clip the camera at the right.
		 * @param const float InBottom: The value to clip the camera at the bottom.
		 * @param const float InTop: The value to clip the camera at the top.
		 * @param const float InNear: The value to clip the camera at the near.
		 * @param const float InFar: The value to clip the camera at the far.
		 *
		 */
		explicit ACamera(const float InLeft, const float InRight, const float InBottom, const float InTop, const float InNear, const float InFar);

		/**
		 * ACamera SetCamera
		 *
		 * This method updates the camera clipping planes with the new given values.
		 *
		 * @param const float InLeft: The new value to clip the camera at the left.
		 * @param const float InRight: The new value to clip the camera at the right.
		 * @param const float InBottom: The new value to clip the camera at the bottom.
		 * @param const float InTop: The new value to clip the camera at the top.
		 * @param const float InNear: The new value to clip the camera at the near.
		 * @param const float InFar: The new value to clip the camera at the far.
		 *
		 */
		void SetCamera(const float InLeft, const float InRight, const float InBottom, const float InTop, const float InNear, const float InFar);

		/**
		 * ACamera GetView
		 *
		 * This method gets the view matrix from this camera.
		 *
		 * @return NMatrix: The view matrix of the camera.
		 *
		 */
		XMMATRIX GetView(void) const;

		/**
		 * ACamera GetProjection
		 *
		 * This method gets the orthographic projection matrix from this camera.
		 *
		 * @return NMatrix: The projection matrix of the camera.
		 *
		 */
		XMMATRIX GetProjection(void) const;
	};
}