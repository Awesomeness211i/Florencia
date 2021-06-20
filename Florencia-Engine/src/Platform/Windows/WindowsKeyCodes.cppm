module;
#include <stdint.h>
export module WindowsKeyCodes;

export namespace Florencia {

	using KeyCode = uint16_t;

	//Virtual KeyCodes
	enum class WindowsKeyCodes : KeyCode {
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */
		Semicolon = 59, /* ; */
		Equal = 61, /* = */
		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */
		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Backspace = 0x08,
		Tab = 0x09,
		Enter = 0x0D,
		Shift = 0x10,
		Control = 0x11,
		Pause = 0x13,
		CapsLock = 0x14,
		Escape = 0x1B,
		Space = 0x20,
		PageUp = 0x21,
		PageDown = 0x22,
		End = 0x23,
		Home = 0x24,
		Left = 0x25,
		Up = 0x26,
		Right = 0x27,
		Down = 0x28,
		Select = 0x29,
		PrintScreen = 0x2C,
		Insert = 0x2D,
		Delete = 0x2E,
		Help = 0x2F,
		D0 = 0x30, /* 0 */
		D1 = 0x31, /* 1 */
		D2 = 0x32, /* 2 */
		D3 = 0x33, /* 3 */
		D4 = 0x34, /* 4 */
		D5 = 0x35, /* 5 */
		D6 = 0x36, /* 6 */
		D7 = 0x37, /* 7 */
		D8 = 0x38, /* 8 */
		D9 = 0x39, /* 9 */
		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C,
		M = 0x4D,
		N = 0x4E,
		O = 0x4F,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5A,

		/* Keypad */
		KP0 = 0x60,
		KP1 = 0x61,
		KP2 = 0x62,
		KP3 = 0x63,
		KP4 = 0x64,
		KP5 = 0x65,
		KP6 = 0x66,
		KP7 = 0x67,
		KP8 = 0x68,
		KP9 = 0x69,
		KPMultiply = 0x6A,
		KPAdd = 0x6B,
		//KPSeparator = 0x6C,
		KPSubtract = 0x6D,
		KPDecimal = 0x6E,
		KPDivide = 0x6F,

		F1 = 0x70,
		F2 = 0x71,
		F3 = 0x72,
		F4 = 0x73,
		F5 = 0x74,
		F6 = 0x75,
		F7 = 0x76,
		F8 = 0x77,
		F9 = 0x78,
		F10 = 0x79,
		F11 = 0x7A,
		F12 = 0x7B,
		F13 = 0x7C,
		F14 = 0x7D,
		F15 = 0x7E,
		F16 = 0x7F,
		F17 = 0x80,
		F18 = 0x81,
		F19 = 0x82,
		F20 = 0x83,
		F21 = 0x84,
		F22 = 0x85,
		F23 = 0x86,
		F24 = 0x87,
		//F25 = 0x79,
		NumLock = 0x90,
		ScrollLock = 0x91,
		LeftShift = 0xA0,
		RightShift = 0xA1,
		LeftControl = 0xA2,
		RightControl = 0xA3,

		KPEnter = 335,
		KPEqual = 336,


		Menu = 348,
		LeftAlt = 342,
		RightAlt = 346,
		LeftSuper = 343,
		RightSuper = 347,
	};

}