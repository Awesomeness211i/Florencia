#include "Console.h"
#include <Platform/Platform.h>
#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
#include <Platform/Windows/WConsole.h>
#elif defined(FLO_PLATFORM_LINUX)
#include <Platform/Linux/LinuxConsole.h>
#elif defined(FLO_PLATFORM_MACOS)
#include <Platform/MacOS/MacConsole.h>
#endif

namespace Florencia {
	Console* Console::Create(int16 minLength) {
		#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
		return new WConsole(minLength);
		#elif defined(FLO_PLATFORM_LINUX)
		return new LinuxConsole(minLength);
		#elif defined(FLO_PLATFORM_MACOS)
		return new MacConsole(minLength);
		#endif
	}
}