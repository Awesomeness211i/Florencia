#pragma once
#include <Core/Console.h>

namespace Florencia {

	class WConsole : public Console {
	public:
		WConsole(int16_t minLength);
		~WConsole() override;
	private:
		[[nodiscard]] bool CreateNewConsole() override;
		[[nodiscard]] bool ReleaseConsole() override;
		[[nodiscard]] bool AttachParentConsole();
		[[nodiscard]] bool RedirectConsoleIO();
		void AdjustConsoleBuffer();
		int16 m_MinLength;
	};
}