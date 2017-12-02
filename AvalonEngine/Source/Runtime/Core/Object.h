/**
 * Object.h
 * 
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Types.h>

namespace Avalon
{
	class AObject
	{
	private:
		const utf8* Name;

	private:
		virtual void ConstructObject(void);

	protected:
		template<typename T>
		T* Cast(AObject* InObject)
		{
			return dynamic_cast<T*>(InObject);
		}

		template<typename T>
		T* CreateDefaultSubobject(const utf8* InName)
		{
			T* Result = new T();

			AObject* Object = Cast<AObject>(Result);
			Object->ConstructObject();
			Object->Name = InName;

			return Result;
		}
	};
}