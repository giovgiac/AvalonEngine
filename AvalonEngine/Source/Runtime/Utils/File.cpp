/**
 * File.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "File.h"

#include <stdio.h>

namespace Avalon {
	utf8* ReadFile(const utf8* InFilename, uint32* OutLength) {
		utf8* Buffer;
		uint32 Size;
		FILE* File;

		// Open File
		fopen_s(&File, InFilename, "rb");

		// Determine File Size in Bytes
		fseek(File, 0, SEEK_END);
		Size = ftell(File);

		// Allocate Buffer
		Buffer = new utf8[Size + 1];

		// Copy Contents to Buffer
		fseek(File, 0, SEEK_SET);
		fread(Buffer, sizeof(utf8), Size, File);
		fclose(File);

		if (OutLength)
			*OutLength = Size;
		Buffer[Size] = '\0';
		return Buffer;
	}
}