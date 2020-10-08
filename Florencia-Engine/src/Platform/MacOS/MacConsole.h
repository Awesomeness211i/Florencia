#pragma once
#include <Core/Console.h>

namespace Florencia {

	class MacConsole : public Console {
	public:
		bool CreateNewConsole() override;
		bool ReleaseConsole() override;
	private:

	};

}