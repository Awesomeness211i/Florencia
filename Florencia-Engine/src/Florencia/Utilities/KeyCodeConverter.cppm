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

	Key ConvertToUniversalKeyCode(int key) {
		switch (key) {
			case (int)A: return Key::A; case (int)B: return Key::B; case (int)C: return Key::C; case (int)D: return Key::D;
			case (int)E: return Key::E; case (int)F: return Key::F; case (int)G: return Key::G; case (int)H: return Key::H;
			case (int)I: return Key::I; case (int)J: return Key::J; case (int)K: return Key::K; case (int)L: return Key::L;
			case (int)M: return Key::M; case (int)N: return Key::N; case (int)O: return Key::O; case (int)P: return Key::P;
			case (int)Q: return Key::Q; case (int)R: return Key::R; case (int)S: return Key::S; case (int)T: return Key::T;
			case (int)U: return Key::U; case (int)V: return Key::V; case (int)W: return Key::W; case (int)X: return Key::X;
			case (int)Y: return Key::Y; case (int)Z: return Key::Z;
			case (int)D0: return Key::D0; case (int)D1: return Key::D1; case (int)D2: return Key::D2;
			case (int)D3: return Key::D3; case (int)D4: return Key::D4; case (int)D5: return Key::D5;
			case (int)D6: return Key::D6; case (int)D7: return Key::D7; case (int)D8: return Key::D8;
			case (int)D9: return Key::D9;
			case (int)KP0: return Key::KP0; case (int)KP1: return Key::KP1; case (int)KP2: return Key::KP2;
			case (int)KP3: return Key::KP3; case (int)KP4: return Key::KP4; case (int)KP5: return Key::KP5;
			case (int)KP6: return Key::KP6; case (int)KP7: return Key::KP7; case (int)KP8: return Key::KP8;
			case (int)KP9: return Key::KP9;

			case (int)Up: return Key::Up;
			case (int)Tab: return Key::Tab;
			case (int)End: return Key::End;
			case (int)Help: return Key::Help;
			case (int)Home: return Key::Home;
			case (int)Left: return Key::Left;
			case (int)Down: return Key::Down;
			case (int)Right: return Key::Right;
			case (int)Enter: return Key::Enter;
			case (int)Shift: return Key::Shift;
			case (int)Pause: return Key::Pause;
			case (int)KPAdd: return Key::KPAdd;
			case (int)Space: return Key::Space;
			case (int)Comma: return Key::Comma;
			case (int)Minus: return Key::Minus;
			case (int)Slash: return Key::Slash;
			case (int)Equal: return Key::Equal;
			case (int)Period: return Key::Period;
			case (int)Escape: return Key::Escape;
			case (int)PageUp: return Key::PageUp;
			case (int)Insert: return Key::Insert;
			case (int)Delete: return Key::Delete;
			case (int)Select: return Key::Select;
			case (int)Control: return Key::Control;
			case (int)NumLock: return Key::NumLock;
			case (int)KPDivide: return Key::KPDivide;
			case (int)PageDown: return Key::PageDown;
			case (int)CapsLock: return Key::CapsLock;
			case (int)Backslash: return Key::Backslash;
			case (int)Semicolon: return Key::Semicolon;
			case (int)KPDecimal: return Key::KPDecimal;
			case (int)Backspace: return Key::Backspace;
			case (int)LeftShift: return Key::LeftShift;
			case (int)KPSubtract: return Key::KPSubtract;
			case (int)KPMultiply: return Key::KPMultiply;
			case (int)Apostrophe: return Key::Apostrophe;
			case (int)RightShift: return Key::RightShift;
			case (int)ScrollLock: return Key::ScrollLock;
			case (int)PrintScreen: return Key::PrintScreen;
			case (int)LeftControl: return Key::LeftControl;
			case (int)GraveAccent: return Key::GraveAccent;
			case (int)LeftBracket: return Key::LeftBracket;
			case (int)RightControl: return Key::RightControl;
			case (int)RightBracket: return Key::RightBracket;
		}
		return (Key)-1;
	}

}