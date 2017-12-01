/**
 * Event.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

namespace Avalon {
	/**
	 * AEventHandler Class
	 *
	 * This class is responsible for creating delegate-style event handlers.
	 *
	 */
	template<typename... ParamType>
	class AEventHandler {
	private:
		/**
		 * AEventFather Class
		 *
		 * This helper class provides a general method without needing ClassType and ReturnType.
		 *
		 */
		template<typename... ParamType>
		class AEventFather {
		public:
			virtual void CallFunction(ParamType... InArgs) = 0;
		};

		/**
		 * AEvent Class
		 *
		 * This class stores the object and function to call.
		 *
		 */
		template<typename ClassType, typename ReturnType, typename... ParamType>
		class AEvent : public AEventFather<ParamType...> {
		public:
			ClassType* Object;
			ReturnType(ClassType::*Function)(ParamType...);

			inline virtual void CallFunction(ParamType... InArgs) override {
				(Object->*Function)(InArgs...);
			}
		};

	private:
		AEventFather<ParamType...>* Event;
		
	public:
		/**
		 * AEventHandler Constructor
		 *
		 * This constructor creates an event handler by receiving and object and a function to call on it.
		 *
		 */
		template<typename ClassType, typename ReturnType>
		inline explicit AEventHandler(ClassType* InObject, ReturnType(ClassType::*InFunction)(ParamType...)) {
			AEvent<ClassType, ReturnType, ParamType...>* EventTmp = new AEvent<ClassType, ReturnType, ParamType...>();

			// Set Stuff
			EventTmp->Object = InObject;
			EventTmp->Function = InFunction;

			// Set Event
			Event = EventTmp;
		}

		/**
		 * AEventHandler Destructor
		 *
		 * This destructor cleans up the memory used up by the event.
		 *
		 */
		inline ~AEventHandler(void) {
			if (Event)
				delete Event;
		}

		/**
		 * AEventHandler Call
		 *
		 * This method calls the function that is stored in the event handler.
		 *
		 */
		inline void Call(ParamType... InArgs) {
			Event->CallFunction(InArgs...);
		}
	};
}