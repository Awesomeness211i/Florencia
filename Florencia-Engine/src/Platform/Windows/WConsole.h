#pragma once
#include <Core/Console.h>

namespace Florencia {

	class WConsole : public Console {
	public:
		WConsole(int16_t minLength);
		~WConsole() override;
	private:
		bool CreateNewConsole() override;
		bool ReleaseConsole() override;
		void AdjustConsoleBuffer();
		bool AttachParentConsole();
		bool RedirectConsoleIO();
		int16_t m_MinLength;
	};
}