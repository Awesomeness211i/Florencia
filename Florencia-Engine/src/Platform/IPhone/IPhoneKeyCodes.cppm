module;
#include <stdint.h>
export module IPhoneKeyCodes;

export namespace Florencia {

	enum class IPhoneKeyCodes : uint16_t {
		A, B, C, D,
		E, F, G, H,
		I, J, K, L,
		M, N, O, P,
		Q, R, S, T,
		U, V, W, X,
		Y, Z,
		F1, F2, F3, F4,
		F5, F6, F7, F8,
		F9, F10, F11, F12,
		F13, F14, F15, F16,
		F17, F18, F19, F20,
		F21, F22, F23, F24,
		F25,
		D0, D1, D2, D3,
		D4, D5, D6, D7,
		D8, D9,
		KP0, KP1, KP2, KP3,
		KP4, KP5, KP6, KP7,
		KP8, KP9,

		Tab,
		KPAdd,
		Space,
		Comma, /* , */
		Minus, /* - */
		Slash, /* / */
		Equal, /* = */
		Period, /* . */
		KPDivide,
		Backslash,  /* \ */
		Semicolon, /* ; */
		KPDecimal,
		KPSubtract,
		KPMultiply,
		Apostrophe, /* ' */
		GraveAccent,  /* ` */
		LeftBracket,  /* [ */
		RightBracket,  /* ] */

		Up,
		End,
		Help,
		Home,
		Left,
		Down,
		Right,
		Enter,
		Shift,
		Pause,
		Escape,
		PageUp,
		Insert,
		Delete,
		Select,
		Control,
		NumLock,
		PageDown,
		CapsLock,
		Backspace,
		PrintScreen,

		LeftShift,
		RightShift,
		ScrollLock,
		LeftControl,
		RightControl,

		//Menu = 348,
		//LeftAlt = 342,
		//RightAlt = 346,
		//LeftSuper = 343,
		//RightSuper = 347,
		//World1 = 161, /* non-US #1 */
		//World2 = 162, /* non-US #2 */
	};

}