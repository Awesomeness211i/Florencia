export module CreateFunctions.Console;
import <Florencia/Core/PlatformDetection.h>;
export import Console;
import WindowsConsole;
import LinuxConsole;

namespace Florencia {

	export Console* CreateConsole() {
		#if defined(FLO_PLATFORM_WINDOWS_64)
		return new WindowsConsole();
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