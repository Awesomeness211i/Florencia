#include "Renderer.h"
#include <Platform/Platform.h>

#ifdef FLO_PLATFORM_WINDOWS
	#include <Platform/Windows/WRenderer.h>
#elif defined(FLO_PLATFORM_WINDOWS_32)
	#include <Platform/Windows/WRenderer.h>
#endif

namespace Florencia {

	Renderer* Renderer::Create() {
		#ifdef FLO_PLATFORM_WINDOWS
		return new WRenderer();
		#elif defined(FLO_PLATFORM_WINDOWS_32)
		return new WRenderer();
		#endif
		return nullptr;
	}

}