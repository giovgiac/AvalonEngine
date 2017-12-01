/**
 * File.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Types.h>

namespace Avalon {
	/**
	 * ReadFile Function
	 *
	 * This function reads a given text file from disk and allocates a buffer to hold it in memory.
	 *
	 * @param const utf8* InFilename: The path to the file to be read.
	 * @param uint32* OutLength: The size of the allocated buffer with the contents.
	 *
	 */
	extern utf8* ReadFile(const utf8* InFilename, uint32* OutLength = nullptr);
}