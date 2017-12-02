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

	protected:
		class AWorld* GetWorld(void) const;

	public:
		AActor(void);

		AActor(XMFLOAT2 InPosition, class AMaterial* InMaterial);

		virtual void Destroy(void);

		virtual void Start(void);

		virtual void Tick(float InDeltaTime);

		void SetTransform(STransform InTransform);

		void SetWorld(AWorld* InWorld);

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