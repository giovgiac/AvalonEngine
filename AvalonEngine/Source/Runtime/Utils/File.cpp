/**
 * File.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "File.h"

#include <fstream>

namespace Avalon {
	TArray<uint8>* ReadShader(const utf8* InFilename)
	{
		TArray<uint8>* Data = nullptr;

		std::ifstream ShaderFile(InFilename, std::ios::in | std::ios::binary | std::ios::ate);
		if (ShaderFile.is_open())
		{
			uint64 Length = static_cast<uint64>(ShaderFile.tellg());

			Data = new TArray<uint8>(Length);

			ShaderFile.seekg(0, std::ios::beg);
			ShaderFile.read(reinterpret_cast<char*>(Data->data()), Length);
			ShaderFile.close();
		}

		return Data;
	}
}