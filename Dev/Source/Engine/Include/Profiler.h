#pragma once

#include <string>

namespace FRE
{
	class ProfileBase
	{
	public:
		virtual unsigned GetCount() const = 0;
		virtual int GetTime(int num) const = 0;
	};

	class CPUProfile : public ProfileBase
	{
	public:
		virtual unsigned GetCount() const override;
		virtual int GetTime(int num) const override;
	};

	class Profiler
	{
	public:
		static Profiler & GetInstance();

		void BeginFrame();
		void EndFrame();
	};
}