#include "Console.h"
#include "Platform/Platform.h"
#ifdef FLO_PLATFORM_WINDOWS
#include "Platform/Windows/WConsole.h"
#elif defined(FLO_PLATFORM_WINDOWS_32)
#include "Platform/Windows/WConsole.h"
#endif

namespace Florencia {
	Console* Console::Create(int16_t minLength) {
		#ifdef FLO_PLATFORM_WINDOWS
		return new WConsole(minLength);
		#endif
		#ifdef FLO_PLATFORM_WINDOWS_32
		return new WConsole(minLength);
		#endif
	}
}