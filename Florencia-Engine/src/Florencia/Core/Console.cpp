module;
#include <Florencia/Core/PlatformDetection.h>
module Console;
#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
import WConsole;
#elif defined(FLO_PLATFORM_LINUX)
import LinuxConsole;
#elif defined(FLO_PLATFORM_MACOS)
import MacConsole;
#elif defined(FLO_PLATFORM_IPHONE) || defined(FLO_PLATFORM_IPHONE_SIMULATOR)
import IPhoneConsole;
#elif defined(FLO_PLATFORM_ANDROID)
import AndroidConsole;
#endif
import Window;

namespace Florencia {

	Console* Console::Create() {
		switch (Window::GetPlatform()) {
			case Window::Platform::None: return nullptr;
		#if defined(FLO_PLATFORM_WINDOWS) || defined(FLO_PLATFORM_WINDOWS_32)
			case Window::Platform::Windows: return new WConsole();
		#elif defined(FLO_PLATFORM_MACOS)
			case Window::Platform::MacOS: return new MacWindow(props);
		#elif defined(FLO_PLATFORM_LINUX)
			case Window::Platform::Linux: return new LinuxWindow(props);
		#elif defined(FLO_PLATFORM_IPHONE) || defined(FLO_PLATFORM_IPHONE_SIMULATOR)
			case Window::Platform::IPhone: return new IPhoneWindow(props);
		#elif defined(FLO_PLATFORM_ANDROID)
			case Window::Platform::Android: return new AndroidWindow(props);
		#endif
		}
		return nullptr;
	}
}