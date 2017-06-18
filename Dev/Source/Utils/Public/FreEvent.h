#pragma once

#include <freutils_export.h>

namespace FRE
{
	namespace Utils
	{
		class Event
		{
		public:
			typedef int EventType;

			virtual bool IsA(EventType type) = 0;
		};

		template<typename _Ty>
		class EventBase
		{

		};
	}
}
