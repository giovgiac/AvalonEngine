/**
 * Types.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

// STL Containers
#include <list>
#include <memory>
#include <vector>

// DirectX Collision, Colors & Math Libraries
#include <DirectXCollision.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

// Project Types
#include <Graphics/Vertex.h>
#include <Math/Transform.h>

// The unsigned byte type
typedef unsigned char uint8;

// The unsigned word type
typedef unsigned short int uint16;

// The unsigned double word type
typedef unsigned int uint32;

// The unsigned quad word type
typedef unsigned long long int uint64;

// The signed byte type
typedef signed char int8;

// The signed word type
typedef signed short int int16;

// The signed double word type
typedef signed int int32;

// The signed quad word type
typedef signed long long int int64;

// The UTF-8 char type
typedef char utf8;

// The UTF-16 char type
typedef wchar_t utf16;

// The UTF-32 char type
typedef int utf32;

// The array type
template<typename T>
using TArray = std::vector<T>;

// The list type
template<typename T>
using TList = std::list<T>;

// The shared pointer type
template<typename T>
using TSharedPtr = std::shared_ptr<T>;

// Using DirectX namespace
using namespace DirectX;
using namespace DirectX::PackedVector;