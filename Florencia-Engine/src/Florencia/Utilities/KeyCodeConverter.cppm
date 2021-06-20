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

	int ConvertToUniversalKeyCode(int key) {
		switch (key) {
			//TODO: Come back and finish all cases
			case (int)D0: return (int)Key::D0;
			case (int)D1: return (int)Key::D1;
			case (int)D2: return (int)Key::D2;
			case (int)D3: return (int)Key::D3;
			case (int)D4: return (int)Key::D4;
			case (int)D5: return (int)Key::D5;
			case (int)D6: return (int)Key::D6;
			case (int)D7: return (int)Key::D7;
			case (int)D8: return (int)Key::D8;
			case (int)D9: return (int)Key::D9;
			case (int)A: return (int)Key::A;
			case (int)B: return (int)Key::B;
			case (int)C: return (int)Key::C;
			case (int)D: return (int)Key::D;
			case (int)E: return (int)Key::E;
			case (int)F: return (int)Key::F;
			case (int)G: return (int)Key::G;
			case (int)H: return (int)Key::H;
			case (int)I: return (int)Key::I;
			case (int)J: return (int)Key::J;
			case (int)K: return (int)Key::K;
			case (int)L: return (int)Key::L;
			case (int)M: return (int)Key::M;
			case (int)N: return (int)Key::N;
			case (int)O: return (int)Key::O;
			case (int)P: return (int)Key::P;
			case (int)Q: return (int)Key::Q;
			case (int)R: return (int)Key::R;
			case (int)S: return (int)Key::S;
			case (int)T: return (int)Key::T;
			case (int)U: return (int)Key::U;
			case (int)V: return (int)Key::V;
			case (int)W: return (int)Key::W;
			case (int)X: return (int)Key::X;
			case (int)Y: return (int)Key::Y;
			case (int)Z: return (int)Key::Z;
			case (int)KP0: return (int)Key::KP0;
			case (int)KP1: return (int)Key::KP1;
			case (int)KP2: return (int)Key::KP2;
			case (int)KP3: return (int)Key::KP3;
			case (int)KP4: return (int)Key::KP4;
			case (int)KP5: return (int)Key::KP5;
			case (int)KP6: return (int)Key::KP6;
			case (int)KP7: return (int)Key::KP7;
			case (int)KP8: return (int)Key::KP8;
			case (int)KP9: return (int)Key::KP9;
		}
		return -1;
	}

}