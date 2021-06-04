#pragma once
#include <stdint.h>

namespace Florencia {

	class WConsole {
	public:
		WConsole(int16_t minLength = 1024) :m_MinLength(minLength) {}
		bool CreateNewConsole();
		bool ReleaseConsole();
	private:
		bool AttachParentConsole();
		bool RedirectConsoleIO();
		void AdjustConsoleBuffer();
		int16_t m_MinLength;
	};
}
