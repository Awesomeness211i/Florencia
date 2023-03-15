#pragma once

namespace Florencia {

	class Console {
	public:
		Console();
		~Console();

		bool AllocateConsole();
		bool ReleaseConsole();
	};

}