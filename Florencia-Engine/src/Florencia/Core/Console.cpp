module;
#include <Florencia/Core/PlatformDetection.h>
module Console;
import WConsole;
import LinuxConsole;
import MacConsole;
import IPhoneConsole;
import AndroidConsole;
import Window;

namespace Florencia {

	Console* Console::Create() {
		#if defined(FLO_PLATFORM_WINDOWS_64) || defined(FLO_PLATFORM_WINDOWS_32)
		return new WConsole();
		#elif defined(FLO_PLATFORM_MACOS)
		return new MacConsole();
		#elif defined(FLO_PLATFORM_LINUX)
		return new LinuxConsole();
		#elif defined(FLO_PLATFORM_IPHONE) || defined(FLO_PLATFORM_IPHONE_SIMULATOR)
		return new IPhoneConsole();
		#elif defined(FLO_PLATFORM_ANDROID)
		return new AndroidConsole();
		#endif
		return nullptr;
	}
}