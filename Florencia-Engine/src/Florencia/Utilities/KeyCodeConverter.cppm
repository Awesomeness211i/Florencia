module;
#include <Florencia/Core/PlatformDetection.h>
export module KeyCodeConverter;

import KeyCodes;
import MacOSKeyCodes;
import LinuxKeyCodes;
import IPhoneKeyCodes;
import AndroidKeyCodes;
import WindowsKeyCodes;

export namespace Florencia {

	int ConvertToUniversalKeyCode(int key) {
		#if defined(FLO_PLATFORM_WINDOWS_64) || defined(FLO_PLATFORM_WINDOWS_32)
		using enum WindowsKeyCodes;
		#elif defined(FLO_PLATFORM_MACOS)
		using enum MacOSKeyCodes;
		#elif defined(FLO_PLATFORM_LINUX)
		using enum LinuxKeyCodes;
		#elif defined(FLO_PLATFORM_IPHONE) || defined(FLO_PLATFORM_IPHONE_SIMULATOR)
		using enum IPhoneKeyCodes;
		#elif defined(FLO_PLATFORM_ANDROID)
		using enum AndroidKeyCodes;
		#endif
		switch (key) {
			//TODO: Come back and finish all cases
			case (int)A: return (int)Key::A;
		}
		return -1;
	}

}