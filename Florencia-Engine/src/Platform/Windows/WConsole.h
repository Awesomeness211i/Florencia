#pragma once
#include <Math/FloMath.h>

namespace Florencia {

	class WConsole {
	public:
		WConsole(int16_t minLength = 1024)
			:m_MinLength(minLength)
		{}
		bool CreateNewConsole();
		bool ReleaseConsole();
	private:
		bool AttachParentConsole();
		bool RedirectConsoleIO();
		void AdjustConsoleBuffer();
		int16 m_MinLength;
	};
}