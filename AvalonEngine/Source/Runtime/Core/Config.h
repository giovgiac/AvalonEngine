/**
 * Config.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Types.h>

namespace Avalon {
	/**
	 * This configuration sets the default vertex shader file to be loaded by the shader.
	 */
	static const utf8* DefaultVertexFilename = "DefaultVertex.cso";

	/**
	 * This configuration sets the default fragment shader file to be loaded by the shader.
	 */
	static const utf8* DefaultFragmentFilename = "DefaultPixel.cso";

	/**
	 * This configuration sets the default clipping number for the near of the orthographic projection.
	 */
	static const float DefaultCameraNear = -1.0f;

	/**
	 * This configuration sets the default clipping number for the far of the orthographic projection.
	 */
	static const float DefaultCameraFar = 1.0f;

	/**
	 * This configuration sets the default width for the scenes.
	 */
	static const float DefaultSceneWidth = 1280.0f;

	/**
	 * This configuration sets the default height for the scenes.
	 */
	static const float DefaultSceneHeight = 768.0f;

	/** 
	 * This configuration sets the default width for windows.
	 */
	static const uint32 DefaultWindowWidth = 1280;

	/**
	 * This configuration sets the default height for windows.
	 */
	static const uint32 DefaultWindowHeight = 768;

	/**
	 * This configuration sets the default title for windows.
	 */
	static const utf8* DefaultWindowTitle = "Avalon Game";

	/**
	 * This configuration sets whether the window is fullscreen by default.
	 */
	static const bool DefaultWindowFullscreen = false;
}