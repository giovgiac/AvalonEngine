/**
 * Actor.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Object.h>

namespace Avalon
{
	class AActor : public AObject
	{
	private:
		TArray<class AActorComponent*> Components;
		STransform Transform;
		class AWorld* World;

	private:
		virtual void ConstructObject(void);

	protected:
		class AWorld* GetWorld(void) const;

	public:
		AActor(void);

		virtual void Destroy(void);

		virtual void Start(void);

		virtual void Tick(float DeltaTime);

		template<typename T>
		TArray<T*> GetComponentsByClass(void)
		{
			TArray<T*> Result;

			for (uint32 i = 0; i < Components.size(); i++)
			{
				T* Component = Cast<T>(Components[i]);
				if (Component)
					Result.push_back(Component);
			}

			return Result;
		}
	};
}