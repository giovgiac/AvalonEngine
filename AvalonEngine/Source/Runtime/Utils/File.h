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
	 * ReadShader Function
	 *
	 * This function reads a given text file from disk and allocates a buffer to hold it in memory.
	 *
	 * @param const utf8* InFilename: The path to the file to be read.
	 * @param uint32* OutLength: The size of the allocated buffer with the contents.
	 *
	 */
	extern TArray<uint8>* ReadShader(const utf8* InFilename);
}