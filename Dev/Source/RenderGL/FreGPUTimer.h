#pragma once

#include "FreProfiler.h"
#include "gl/glew.h"

namespace FRE
{
	namespace Utils
	{
		class GPUTimer
		{
		public:
			GPUTimer();
			~GPUTimer();

			void Start();
			void Stop();

			double GetTime();

		private:
			GLuint _handle;
			GLint _available;
			GLuint64 _time;
		};

		typedef FProfileMarkerT<GPUTimer> FGPUMarker;
	}
}

#define GPU_PROFILE_START(name) { FGPUMarker _##name(#name); _##name.Start(); 
#define GPU_PROFILE_STOP(name) _##name.Stop(); }